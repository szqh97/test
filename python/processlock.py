# coding: utf-8  
# processlock.py  
# 进程锁 - 进程间互斥锁  
  
import os  
try:  
    import fcntl  
    LOCK_EX = fcntl.LOCK_EX  
except ImportError:  
    # Windows平台下没有fcntl模块  
    fcntl = None  
    import win32con  
    import win32file  
    import pywintypes  
    LOCK_EX = win32con.LOCKFILE_EXCLUSIVE_LOCK  
    overlapped = pywintypes.OVERLAPPED()  
  
class Lock:  
    """进程锁 
    """  
      
    def __init__(self, filename='processlock.pid'):  
        self.filename = filename  
        # 如果文件不存在则创建  
        self.handle = open(filename, 'w')  
  
    def acquire(self):  
        # 给文件上锁  
        if fcntl:  
            fcntl.flock(self.handle, LOCK_EX)  
        else:  
            hfile = win32file._get_osfhandle(self.handle.fileno())  
            win32file.LockFileEx(hfile, LOCK_EX, 0, -0x10000, overlapped)  
  
    def release(self):  
        # 文件解锁  
        if fcntl:  
            fcntl.flock(self.handle, fcntl.LOCK_UN)  
        else:  
            hfile = win32file._get_osfhandle(self.handle.fileno())  
            win32file.UnlockFileEx(hfile, 0, -0x10000, overlapped)  
  
    def __del__(self):  
        try:  
            self.handle.close()  
            os.remove(self.filename)  
        except:  
            print "ee"
            pass  

  
if __name__ == '__main__':  
    # 测试：依次运行本程序多个实例，第N个实例运行耗时是第一个的N倍  
    
    import time  
    import os
    print 'Time: %s' % time.time()  
    start = time.time()
  
    lock = Lock()  
    try:  
        lock.acquire()  
        with file( './a.txt', 'a+') as f:
            f.seek(2)
            f.write(str(start) + ", " + str(os.getpid()) + '\n')
    finally:   
        lock.release()  

    end = time.time()
    print 'Time: %s' % time.time()  

    print "cost: %d" % (end-start)
