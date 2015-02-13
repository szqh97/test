#/usr/bin/env python
# -*- coding:utf-8 -*-
from tornado import ioloop
from tornado import iostream
import socket
# 当connect()函数完成后，调用本函数
# 本函数在非阻塞异步写 write 后
# 异步读取以\r\n\r\n 结尾的数据，并调用回调 on_headers
def send_request():
    stream.write("GET / HTTP/1.0\r\nHost: friendfeed.com\r\n\r\n")
    stream.read_until("\r\n\r\n", on_headers)
# 当读取到以\r\n\r\n结尾的数据的时候，触发 on_headers回调函数，
# 并传入参数 data（次data数据以\r\n\r\n结尾） 到 on_headers中
def on_headers(data):
    headers = {}
    for line in data.split("\r\n"):
       parts = line.split(":")
       if len(parts) == 2:
           headers[parts[0].strip()] = parts[1].strip()
# 读取完header后，根据读取到的length 触发 on_body 函数，整个过程都是异步的
    print headers.keys()
    stream.read_bytes(int(headers["Content-Length"]), on_body)

def on_body(data):
    #print data
    stream.close()
    ioloop.IOLoop.instance().stop()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
# 创建一个流的实例，绑定描述符 s
stream = iostream.IOStream(s)
# 连接并放置相应的回调 send_request，这里后面的操作都是纯异步实现的
# connect完成后触发 send_request的调用
stream.connect(("friendfeed.com", 80), send_request)
ioloop.IOLoop.instance().start()
