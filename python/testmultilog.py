#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
这是一个demo，用来演示多进程、多线程程序在使用日志轮转时会发生问题：
Traceback (most recent call last):
  File "C:\Python32\lib\logging\handlers.py", line 78, in emit
    self.doRollover()
  File "C:\Python32\lib\logging\handlers.py", line 140, in doRollover
    os.rename(self.baseFilename, dfn)
WindowsError: [Error 32] 另一个程序正在使用此文件，进程无法访问。
'''
import sys
import logging,logging.handlers
import os
import time
import threading as th
import multiprocessing as mp

def myprint(obj, end='\n'):
    sys.stdout.write(str(obj) + end)

def setuplogger(argsdict):
    '''
    建立logger对象
    '''
    LOGGINGLEVEL = {
        'notset': logging.NOTSET,
        'debug': logging.DEBUG,
        'info': logging.INFO,
        'warning': logging.WARNING,
        'error': logging.ERROR,
        'critical': logging.CRITICAL,
        }
    logfn=argsdict['logfilename']
    loglevel=LOGGINGLEVEL[argsdict['loglevel']]
    # setup logger object
    mylogger = logging.getLogger(argsdict['loggername'])
    # set log level
    mylogger.setLevel(loglevel)
    # handler
    handler = logging.handlers.RotatingFileHandler(logfn,
            maxBytes=argsdict['maxlogsize'],
            backupCount=argsdict['backupcount'])
    formatter = \
        logging.Formatter('%(asctime)s - %(name)s - %(levelname)s :: %(message)s'
                          )
    handler.setFormatter(formatter)
    # add handler to logger
    mylogger.addHandler(handler)
    # return logger object
    return mylogger

def thlogfunc(appargs,qlog):
    '''
    日志记录线程工作函数
    appargs:应用程序参数字典
    qlog:读取日志信息的队列
    '''
    # 建立日志记录对象
    logger = setuplogger(appargs)

    while True:
        bf = qlog.get()
        #读取到None时表示程序要退出了
        if bf is None:
            break

        level,loginfo=bf
        if level.lower()=='debug':
            logger.debug(loginfo)
        elif level.lower()=='info':
            logger.info(loginfo)
        elif level.lower()=='warning':
            logger.info(loginfo)
        elif level.lower()=='error':
            logger.info(loginfo)
        elif level.lower()=='critical':
            logger.info(loginfo)

def pfunc(qlog):
    '''
    子进程工作函数
    '''
    pid=os.getpid()
    info='subprocess [%d] started.' % pid
    myprint(info)
    qlog.put(('info',info))
    for i in range(200):
        info='subprocess [%d]:%d this is test message come from subprocess.' % (pid,i)
        qlog.put(('info',info))
    info='subprocess [%d] stopped.' % pid
    myprint(info)
    qlog.put(('info',info))

def main():
    try:
        appargs={   'loggername': 'app',
                    'logfilename': 'app.log',
                    'loglevel': 'debug',
                    'maxlogsize': 50000,   #50kb
                    'backupcount': 5,        }
        qlog=mp.Queue()
        thlog=th.Thread(target=thlogfunc,args=(appargs,qlog))
        #must be logging in subprocess
        #thlog=mp.Process(target=thlogfunc,args=(appargs,qlog))
        thlog.start()
        thid=thlog.ident
        #thid=11
        info='thread [%d] started.' % thid
        myprint(info)
        qlog.put(('info',info))

        ps=[mp.Process(target=pfunc,args=(qlog,)) for i in range(10)]
        for p in ps:
            p.start()

        for p in ps:
            p.join()

    except Exception as ex:
        exinfo=str(ex)
        myprint(exinfo)
        qlog.put(('info',exinfo))

    finally:
        if thlog.is_alive:
            qlog.put(None)
            thlog.join()
            info='thread [%d] stopped.' % thid
            myprint(info)

if __name__ == '__main__':
    main()
    myprint('done')
