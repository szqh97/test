#!/usr/bin/env python

def func():
    try:
        f = file('./c.txt', 'r')
        #f.close()
        print "ccc"
        return 0
        pass

    except Exception, err:
        pass
    finally:
        print 'close file'
        f.close()

func()
