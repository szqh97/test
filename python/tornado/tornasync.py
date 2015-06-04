#!/usr/bin/env python
'''
Author: szqh97@163.com
Date  : 2015-06-04 14:02:05 

'''

import multiprocessing.queues as Queue
import multiprocessing.pool as Pool
from multiprocessing import Queue

import constant
class TornasyncException(Exception):
    constant.ERR_UNKNOW      = 0
    constant.ERR_NOT_STARTED = 1
    constant.ERR_TOO_BUSY    = 2
    constant.ERR_STOPED      = 3
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

class Tarsync(object):

    _quit = False
    _pool_size = 0
    _idle_objs_pool = None
    _pending_objs_pool = None

    @classmethod
    def has_pendings(cls):
        return cls._pending_objs_pool is not None and not cls._pending_objs_pool.empty()

    @classmethod
    def start_Tarsync(cls, poolsize):

        if cls._pending_objs_pool is not None:
            # Tarsync has already run
            return
        cls._quit = False
        cls._pool_size = poolsize
        cls._pending_objs_pool = Queue(cls._pool_size)

    @classmethod
    def _worker_process(cls):
        while not cls._quit:
            tasync_obj = cls._pending_objs_pool.get(block = True)
            tasync_obj._run()

            # tasync_obj is idling after running.
            cls._idle_objs_pool.put(tasync_obj)
    
    @classmethod
    def _run(cls):
        pass



