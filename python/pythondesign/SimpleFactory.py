#!/usr/bin/env python

class SimpleFactory(object):
    @staticmethod
    def build_conncetion(protocol):
        if protocol == 'http':
            return HTTPConnection()
        elif protocol == 'ftp':
            return FTPConnection()
        else:
            return RuntimeError("Unkown protocal")
if __name__ == '__main__':
    protocal = raw_input('Which Protocol to use?(http or ftp):')
    protocal = SimpleFactory.build_conncetion(protocal)
    protocal.connect()
    print protocal.get_response()

