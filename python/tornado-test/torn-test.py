#!/usr/bin/env python
# -*- coding: utf-8 -*-

import errno
import functools
import tornado.ioloop
import socket
import time

def ontimer(ioloop):
    print 'this running at ', time.ctime()
    ioloop.add_timeout(time.time() + 3, ontimer, ioloop)

def handle_connection(connection, address):
    connection.send('hello')

def connection_ready(sock, fd, events):
    while True:
        try:
            connection, address = sock.accept()
        except socket.error as e:
            if e.args[0] not in (errno.EWOULDBLOCK, errno.EAGAIN):
                raise
            return
        connection.setblocking(0)
        handle_connection(connection, address)

if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.setblocking(0)
    sock.bind(("", 8899))
    sock.listen(128)

    io_loop = tornado.ioloop.IOLoop.current()
    callback = functools.partial(connection_ready, sock)
    io_loop.add_handler(sock.fileno(), callback, io_loop.READ)
    io_loop.add_timeout(time.time() + 3, ontimer, io_loop)
    io_loop.start()


