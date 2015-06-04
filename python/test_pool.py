#!/usr/bin/env python
from multiprocessing import Pool

import time
def f(x):
    time.sleep(4)
    return x

pool = Pool(processes = 4)


for i in xrange(40):
    result = pool.apply_async(f, (i,))
print result.get(timeout = 19)
