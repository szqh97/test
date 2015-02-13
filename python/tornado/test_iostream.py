#!/usr/bine/env python
import tornado
from tornado.iostream import IOStream
import socket

def read_from_server():


    pass
    



sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
sio = IOStream(sock)

host = ('localhost', 8899)
future = sio.connect(host)


