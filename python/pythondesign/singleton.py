#!/usr/bin/env python
## 
##
##
class Singelton(object):
    def __new__(cls):
        if not hasattr(cls, "instance"):
            cls.instance = super(Singelton, cls).__new__(cls)
        return cls.instance

class Borg(object):
    _shared_state = {}

    def __new__(cls, *args, **kwargs):
        obj = super(Borg, cls).__new__(cls, *args, **kwargs)
        obj.__dict__ = cls._shared_state
        return obj
