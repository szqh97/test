#!/usr/bin/env python
# -*- coding: utf-8 -*-
from tornado.tcpserver import TCPServer
from tornado.ioloop import IOLoop

class Demo(TCPServer):
    def handle_stream(self, sockfd, client_addr):
        print  "called handle_stream", client_addr
        print sockfd.read_bytes(10, self.handle_recv)

    def handle_recv(self, data):
        print data

if __name__ == '__main__':
    d = Demo()
    d.listen(12345, address="0.0.0.0")
    IOLoop.instance().start()

