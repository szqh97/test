#!/usr/bin/env python
# -*- coding:utf-8 -*-
#
#   Author  :   cold
#   E-mail  :   wh_linux@126.com
#   Date    :   13/04/15 15:08:51
#   Desc    :   Tornado Echo Server
#   HOME    :   http://www.linuxzen.com
#
import Queue
import socket

from functools import partial

from tornado.ioloop import IOLoop

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setblocking(0)              # 将socket设置为非阻塞

server_address = ("localhost", 10000)

sock.bind(server_address)
sock.listen(5)

fd_map = {}              # 文件描述符到socket的映射
message_queue_map = {}   # socket到消息队列的映射

fd = sock.fileno()
fd_map[fd] = sock

ioloop = IOLoop.instance()

def handle_client(cli_addr, fd, event):
    s = fd_map[fd]
    if event & IOLoop.READ:
        data = s.recv(1024)
        if data:
            print "     received '%s' from %s" % (data, cli_addr)
            # 接收到消息更改事件为写, 用于发送数据到对端
            ioloop.update_handler(fd, IOLoop.WRITE)
            message_queue_map[s].put(data)
        else:
            print "     closing %s" % cli_addr
            ioloop.remove_handler(fd)
            s.close()
            del message_queue_map[s]

    if event & IOLoop.WRITE:
        try:
            next_msg = message_queue_map[s].get_nowait()
        except Queue.Empty:
            print "%s queue empty" % cli_addr
            ioloop.update_handler(fd, IOLoop.READ)
        else:
            print 'sending "%s" to %s' % (next_msg, cli_addr)
            s.send(next_msg)

    if event & IOLoop.ERROR:
        print " exception on %s" % cli_addr
        ioloop.remove_handler(fd)
        s.close()
        del message_queue_map[s]


def handle_server(fd, event):
    s = fd_map[fd]
    if event & IOLoop.READ:
        conn, cli_addr = s.accept()
        print "     connection %s" % cli_addr[0]
        conn.setblocking(0)
        conn_fd = conn.fileno()
        fd_map[conn_fd] = conn
        handle = partial(handle_client, cli_addr[0])   # 将cli_addr作为第一个参数
        #def handle_client(cli_addr, fd, event):
        # 将连接和handle注册为读事件加入到 tornado ioloop
        ioloop.add_handler(conn_fd, handle, IOLoop.READ)
        message_queue_map[conn] = Queue.Queue()   # 创建对应的消息队列


ioloop.add_handler(fd, handle_server, IOLoop.READ)

ioloop.start()


