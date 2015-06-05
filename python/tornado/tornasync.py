#!/usr/bin/env python
'''
Author: szqh97@163.com
Date  : 2015-06-04 14:02:05 

'''

import multiprocessing.queues as Queue
import multiprocessing.pool as Pool
import multiprocessing
from multiprocessing import Queue
import traceback
import logging

import constant
class TornasyncException(Exception):
    constant.ERR_UNKNOW      = 0
    constant.ERR_NOT_STARTED = 1
    constant.ERR_TOO_BUSY    = 2
    constant.ERR_STOPPED     = 3
    constant.ERR_RUN_ERROR   = 4

    def __init__(self, errcode, org_exc = None, org_traceback = None):
        self.err_code = errcode
        self.org_exc = org_exc
        self.org_traceback = org_traceback
        self.err_info_list = [
                "unknow error!", 
                "not started!",
                "tornasync is too busy!",
                "tornasync running error!",
                ]

        def __str__(self):
            return 'exception occurred! ' + self.err_info_list[self.err_code]
    def __repr__(self):
        return str(self)
    def get_error_code(self):
        return self.err_code
    def get_org_exc(self):
        return self.org_exc
    def get_org_traceback(self):
        return self.org_traceback

class Tornasync(object):

    _quit = False
    _pool_size = 0
    _idle_objs_pool = None
    _pending_objs_pool = None

    @classmethod
    def has_pendings(cls):
        return cls._pending_objs_pool is not None and not cls._pending_objs_pool.empty()

    @classmethod
    def start_Tornasync(cls, poolsize):

        if cls._pending_objs_pool is not None:
            # Tarsync has already run
            return
        cls._quit = False
        cls._pool_size = poolsize
        cls._pending_objs_pool = Queue(cls._pool_size)

        for pix in xrange(cls._pool_size):
            p = multiprocessing.Process(None, cls._worker_process)
            p.start()
        cls._idle_objs_pool = Queue(cls._pool_size)
        for ndx in xrange(cls._pool_size):
            cls._idle_objs_pool.put(Tornasync())

    @classmethod
    def stop_Tornasync(cls):
        '''
        '''
        if not cls._pending_objs_pool:
            # Tarsync is not started
            return 

        while not cls._idle_objs_pool.empty():
            cls._idle_objs_pool.get(block = False)

        #FIXME: must consume the pending objects!!
        while not cls._pending_objs_pool.empty():
            cls._pending_objs_pool.get(block = False)

        cls._pool_size = 0
        cls._idle_objs_pool = None
        cls._pending_objs_pool = None

    def __init__(self):
        self._cleanup()

    def _cleanup(self):
        self.callee_callback = lambda: None
        self.callee = lambda: None
        self.args = None
        self.kwarg = None
        self.gen_callback = lambda:None

        self.response = None
        self.error = None
    
    @classmethod
    def run(cls, callee_callback, callee, *args, **kwargs):
        '''
        Call a callee function with args and kwargs in pool
        The Tornasync isshould be a function or method like:
            def Tornasync_ahndler(response, error):
                pass
            clas foo(object):
                def Tornasync_handler(self, response, error):
                    pass
        '''
        if Tornasync._quit:
            raise TornasyncException(constant.ERR_STOPPED)
        if not cls._pending_objs_pool:
            raise TornasyncException(constant.ERR_NOT_STARTED)

        try:
            idle_obj = cls._idle_objs_pool.get(block = False)
        except Queue.Empty:
            raise TornasyncException(constant.ERR_TOO_BUSY)

        idle_obj._cleanup()
        idle_obj.callee_callback = callee_callback
        idle_obj.callee = callee
        idle_obj.args = args
        idle_obj.kwargs = kwargs

        cls._pending_objs_pool.put(idle_obj)

    @classmethod
    def gen_run(cls, callee, *args, **kwargs):
        '''
        this function should used only with tornado.gen
        
        sample:
            response, error = yield tornado.gen.Task(Tornasync.gen_run, someFunc, Arg1, Arg2, ...)
            if error:
                logging.error("org_exc: " + str(error.org_exc()))
            else:
                response_handler(response)
        '''
        if cls._quit :
            raise TornasyncException(constant.ERR_STOPPED)
        if not cls._pending_objs_pool:
            raise TornasyncException(constant.ERR_NOT_STARTED)

        try:
            idle_obj = cls._idle_objs_pool.get(block = False)
        except Queue.Empty:
            raise TornasyncException(constant.ERR_TOO_BUSY)
        idle_obj._cleanup()

        idle_obj.gen_callback = kwargs["callback"]
        del kwargs["callback"]

        idle_obj.callee_callback = idle_obj._gen_run_callback
        idle_obj.callee = callee
        idle_obj.args = args
        idle_obj.kwargs = kwargs

        cls._pending_objs_pool.put(idle_obj)

    @classmethod
    def _worker_process(cls):
        while not cls._quit:
            tasync_obj = cls._pending_objs_pool.get(block = True)
            tasync_obj._run()

            # tasync_obj is idling after running.
            cls._idle_objs_pool.put(tasync_obj)

    def _run(self):
        res = None
        err = None
        try:
            res = self.callee(*self.args, **self.kwarg)
        except Exception as e:
            tb = traceback.format_exc()
            logging.error(" >>>> \n%s\n Tornasync run error: \n %s %s\n", '-' *80, tb, '-' * 80)
            err = TornasyncException(constant.ERR_RUN_ERROR, e, tb)
        
        if self.callee_callback:
            try: 
                self.callee_callback(res, err)
            except Exception as e:
                tb = traceback.format_exc()
                logging.error(" >>>> \n%s\n Tornasync run error: \n %s %s\n", '-' *80, tb, '-' * 80)

    def _gen_run_callback(self, response, error):
        from tornado.ioloop import IOLoop
        
        if error:
            self.error = error
        else:
            self.response = response

        IOLoop.instance().add_callback(self._io_callback)

    def _io_callback(self):
        #restore kwargs for tornado.gen
        self.kwargs['callback'] = self.gen_callback
        self.gen_callback((self.response, self.error))
        self._cleanup()


# for test
if __name__ == '__main__':
    pass
