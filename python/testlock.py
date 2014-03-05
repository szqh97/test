#!/usr/bin/env python
import os
import time

from portalocker import lock, unlock, LOCK_EX

with file ('a.txt', 'r+') as f:
    lock(f, LOCK_EX)
    f.seek(0,2)
    f.write(str(time.time()) + "---" + str(os.getpid()) + '\n')
    unlock(f)

