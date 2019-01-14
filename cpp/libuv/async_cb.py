#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import time
import selectors
import socket

selector = selectors.DefaultSelector()
taks_cnt = 0

def future(url):
    global task_cnt
    task_cnt += 1
    response = []
    request = 'GET {} HTTP/1.1\r\nHOST localhost\r\n\r\n'.format(url)
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.setblocking(False)
    try:
        sock.connect(('localhost', 5000))
    except BlockingIOError:
        pass
    connect_cb = lambda: on_connect(sock, request, response)

def on_connec
