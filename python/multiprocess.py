import multiprocessing
import time
import logging

logger = multiprocessing.log_to_stderr()
logger.setLevel(multiprocessing.SUBDEBUG)

def func(msg):
    for i in xrange(3):
        logger.info("the id is %d", i)
        time.sleep(1)

if __name__ == "__main__":
    pool = multiprocessing.Pool(processes=4)
    for i in xrange(10):
        logger.info(msg)
        msg = "hello %d" %(i)
        pool.apply_async(func, (msg, ))
    time.sleep(10)
    print "Sub-process(es) done."
