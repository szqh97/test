#!/usr/bin/env python
import os
import time

from portalocker import lock, unlock, LOCK_EX

with file ('a.txt', 'a+') as f:
    lock(f, LOCK_EX)
    f.write(str(time.time()) + "---" + str(os.getpid()) + '\n')
    unlock(f)

