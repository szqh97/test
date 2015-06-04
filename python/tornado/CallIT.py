'''
Call In Thread using thread pool
Created on Mar 27, 2012

@author: Hua Hongliang
@email:   huahl@126.com

licensed under APACHE license.

'''

import Queue;
import time;
import threading;
import logging;
import traceback

class CallITException(Exception):
    '''
    Raised by CallIT constructor when not started or none idle thread can be found for its running
    or stopped. RUN_ERROR exception is raised when executing the called if failed
    '''
    NOT_STARTED = 1;
    TOO_BUSY = 2;
    STOPPED = 3;
    RUN_ERROR = 4;

    def __init__(self, errcode, org_exc=None, org_traceback=None):
        '''
        NOT_STARTED, TOO_BUSY or STOPPED
        '''
        self.__error_code = errcode;

        self.__org_exc = org_exc;
        self.__org_traceback = org_traceback;

    def __str__(self):
        return "CallITException(" + ["UNKNOWN", "NOT_STARTED", "TOO_BUSY", "STOPPED", "RUN_ERROR"][self.__error_code] + ")";

    def __repr__(self):
        return str(self);

    def error_code(self):
        return self.__error_code;

    def org_exc(self):
        return self.__org_exc;

    def org_traceback(self):
        return self.__org_traceback;

class CallIT(object):
    '''
    Call functions or method using thread pool.
    '''

    __quit = False;
    __pool_size = 0;
    __pool_pending_calls = None;
    __pool_thread_ids = None;
    __pool_idle_callit_objs = None;

    @classmethod
    def has_pendings(cls):
        '''
        True if pending calls exist
        '''
        return cls.__pool_pending_calls != None and not cls.__pool_pending_calls.empty();

    @classmethod
    def start_pool(cls, poolsize):
        '''
        start thread pool and prepare to handle calling requests.
        poolsize specifies how many threads should be used to run calling requests 
        and should be greater than or equal to 1. 
        '''
        if cls.__pool_pending_calls != None:
            # started already
            return;

        cls.__quit = False;
        cls.__pool_size = poolsize;

        cls.__pool_pending_calls = Queue.Queue(cls.__pool_size);
        cls.__pool_thread_ids = Queue.Queue(cls.__pool_size);

        for ndx in xrange(0, cls.__pool_size):
            t = threading.Thread(None, cls.__worker_thread, "CallIT-" + str(ndx), (ndx,));
            t.start();

        cls.__pool_idle_callit_objs = Queue.Queue(cls.__pool_size);
        for ndx in xrange(0, cls.__pool_size):
            cls.__pool_idle_callit_objs.put(CallIT());


    @classmethod
    def stop_pool(cls):
        if not cls.__pool_pending_calls:
            return;

        cls.__quit = True;

        for ndx in xrange(0, cls.__pool_size):
            try: CallIT.run(None, cls.__dummy_stopping_call);
            except CallITException: pass

        while not cls.__pool_thread_ids.empty():
            time.sleep(0.05);

        while not cls.__pool_pending_calls.empty():    
            cls.__pool_pending_calls.get(block=False);
        while not cls.__pool_idle_callit_objs.empty():    
            cls.__pool_idle_callit_objs.get(block=False);

        cls.__pool_size = 0;
        cls.__pool_thread_ids = None;
        cls.__pool_pending_calls = None;
        cls.__pool_idle_callit_objs = None;


    def __init__(self):
        self.callee_callback = None;
        self.callee = None;
        self.args = None;
        self.kwargs = None;
        self.gen_callback = None;

        self.response = None;
        self.error = None;

    def __cleanup(self):
        self.callee_callback = None;
        self.callee = None;
        self.args = None;
        self.kwargs = None;
        self.gen_callback = None;

        self.response = None;
        self.error = None;

    @classmethod
    def gen_run(cls, callee, *args, **kwargs):
        '''
        Should be used only with tornado.gen

        Using tornado.gen.Task to yield a async call to fucntion callee with args and kwargs.
        The Task will return a tuple of (response, error) when finished, where error is a
        CallITException instance if callee running failed.

        CallITException is raised immediately if failed to start.  

        The class method start_pool(poolsize) should be called before calling this method.

        sample:
            response, error = yield tornado.gen.Task(CallIT.gen_run, someFunc, arg1, arg2, ... );        
            if error:
                logging.debug("org_exc: " + str(error.org_exc()));
                logging.debug("org_traceback: " + error.org_traceback());
            else:
                handle(response);

        '''        

        if CallIT.__quit and callee != CallIT.__dummy_stopping_call:
            raise CallITException(CallITException.STOPPED);
        if not CallIT.__pool_pending_calls:
            raise CallITException(CallITException.NOT_STARTED);

        try:
            idle = cls.__pool_idle_callit_objs.get(block=False);
        except Queue.Empty:
            raise CallITException(CallITException.TOO_BUSY);

        idle.__cleanup();

        idle.gen_callback = kwargs["callback"];
        del kwargs["callback"];

        idle.callee_callback = idle.__gen_run_callback;
        idle.callee = callee;
        idle.args = args;
        idle.kwargs = kwargs;

        # add to pool, try is not need
        CallIT.__pool_pending_calls.put(idle);


    @classmethod
    def run(cls, callee_callback, callee, *args, **kwargs):
        '''        
        Call a callee function with args and kwargs in thread pool and 
        the callee_callback(if not None) with response, error will be 
        called when finished. 

        CallITException is raised immediately if failed to start.  

        The callee_callback should be a function or method like:
            def callit_handler(response, error):
                pass
            class foo(object):
                def callit_handler(self, response, error):
                    pass

        The class method start_pool(poolsize) should be called before this,
        and it can be used directly without tornado.gen

        '''
        if CallIT.__quit and callee != CallIT.__dummy_stopping_call:
            raise CallITException(CallITException.STOPPED);
        if not CallIT.__pool_pending_calls:
            raise CallITException(CallITException.NOT_STARTED);

        try:
            idle = cls.__pool_idle_callit_objs.get(block=False);
        except Queue.Empty:
            raise CallITException(CallITException.TOO_BUSY);

        idle.__cleanup();
        idle.callee_callback = callee_callback;
        idle.callee = callee;
        idle.args = args;
        idle.kwargs = kwargs;

        # add to pool, try is not need
        CallIT.__pool_pending_calls.put(idle);

    def __run(self):
        '''
        Pick up an idle thread and run self.callee in the thread, 
        if failed to found a idle thread, TooBusyException is raised.
        '''
        res = None;
        err = None;
        try:
            res = self.callee(*self.args, **self.kwargs);            
        except Exception as inst:
            tb = traceback.format_exc();
            logging.error(" >>>\n%s\nCallIT run error:\n%s%s\n", '-' * 80, tb, '-' * 80);
            err = CallITException(CallITException.RUN_ERROR, inst, tb);

        if self.callee_callback:
            try:
                self.callee_callback(res, err);
            except Exception as inst:
                tb = traceback.format_exc();
                logging.error(" >>>\n%s\nCallIT uncautch error in callback:\n%s%s\n", '-' * 80, tb, '-' * 80);

    def __gen_run_callback(self, response, error):
        from tornado.ioloop import IOLoop;

        if error:
            self.error = error;
        else:    
            self.response = response;

        # should return to IOLoop thread  
        IOLoop.instance().add_callback(self.__io_callback);

    def __io_callback(self):        
        # restore kwargs for tornado.gen
        self.kwargs["callback"] = self.gen_callback;
        self.gen_callback((self.response, self.error));
        self.__cleanup();


    @classmethod
    def __dummy_stopping_call(cls):
        '''
        dummy task used to stop thread pooling immediately. 
        '''
        pass;

    @classmethod
    def __worker_thread(cls, id):
        logging.info("CallIT worker[%d] started" % id);
        cls.__pool_thread_ids.put(id);
        while not cls.__quit:
            callit = cls.__pool_pending_calls.get(block=True);
            callit.__run();

            cls.__pool_idle_callit_objs.put(callit);


        logging.info("CallIT worker[%d] stopped" % id);
        cls.__pool_thread_ids.get(block=True);


### test        
if __name__ == "__main__":
    logging.basicConfig(**{"level": logging.NOTSET});

    # init CallIT thread pool
    CallIT.start_pool(5);

    def add(a, b=0):
        return a + b;

    class TestObject(object):
        def __init__(self, base=0):
            self._base = base;

        def add(self, addent):
            self._base += addent;
            return self._base;

        def test_kwargs(self, **kwargs):
            return kwargs["email"];

        def test_except(self):
            raise Exception("OK for test! Test Exception.");

        def on_add_result(self, response, error):
            logging.debug("TestObject on_add_result response " + str(response));
            #test callback uncautch exception
            raise Exception("OK for test! And you shouldn't raise error in callback.")

    def callit_handler(response, error):
        if error:
            logging.debug("\tcallit_handler got an error: " + str(error) + "\n");
            return;

        logging.debug("\tcallit_handler finished with no error, response: " + str(response) + "\n");




    logging.debug("CallIT.run(add, 1, 3): ");
    try: CallIT.run(callit_handler, add, 1, b=3);
    except CallITException as e: logging.debug("Failed to start due to %s" % repr(e))

    logging.debug("CallIT().run(TestObject(5).add, 1): ");
    testObj = TestObject(5);
    try: CallIT.run(testObj.on_add_result, testObj.add, 1);
    except CallITException as e: logging.debug("Failed to start due to %s" % repr(e))

    logging.debug("CallIT.run(TestObject().test_kwargs): ");
    try: CallIT().run(callit_handler, TestObject().test_kwargs, **{"email": "huahl@126.com", "name": "huahl"});
    except CallITException as e: logging.debug("Failed to start due to %s" % repr(e))

    logging.debug("CallIT.run(TestObject().test_except): ");
    try: CallIT().run(callit_handler, TestObject().test_except);
    except CallITException as e: logging.debug("Failed to start due to %s" % repr(e))

    while CallIT.has_pendings():
          time.sleep(0.05);

    CallIT.stop_pool();

    while CallIT.has_pendings():
          time.sleep(0.05);

    logging.debug("Application quit!")

