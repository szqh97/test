#!/usr/bin/env python
from itertools import izip
rpc_info = {}
def xmlrpc(in_ = (), out = (type(None), )):
    def _xmlrpc(function):
        func_name = function.func_name
        rpc_info[func_name] = (in_, out)

    def _check_types(elements, types):
        """subfunction that checks the types."""
        if len(elements) != len(types):
            raise TypeError('argument count is wrong')
        typed = enumerate(izip(elements, types))
        for index, couple in typed:
            arg, of_the_right_type = couple
            if isinstance(arg, of_the_right_type):
                continue
            raise TypeError("arg #%d should be %s" % ( index, of_the_right_type))


