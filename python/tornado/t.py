import multiprocessing

class someClass(object):
    def __init__(self):
        pass

    def f(self, x):
        return x*x

    def go(self):
        pool = multiprocessing.Pool(processes=4)            
        result = pool.apply_async(self.f, [10])     
        print result.get(timeout=1)           
        #print pool.map(self.f, range(10))

s = someClass()
s.go()
