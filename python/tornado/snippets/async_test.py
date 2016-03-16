#!/usr/bin/env python
# -*- coding: utf-8 -*-
from tornado.httpclient import HTTPClient, AsyncHTTPClient
from tornado.concurrent import Future
from tornado import gen

def syncronous_fetch(url):
    http_client = HTTPClient()
    response = http_client.fetch(url)
    return response.body

def asynchronous_fetch(url, callback):
    http_client = AsyncHTTPClient()
    def handle_response(response):
        callback(response.body)
    http_client.fetch(url, callback=handle_response)

def async_fetch_future(url):
    http_client = AsyncHTTPClient()
    my_future = Future()
    fetch_future = http_client.fetch(url)
    fetch_future.add_done_callback(
            lambda f: my_future.set_result(f.result())
            )
    return my_future

@gen.coroutine
def fetch_coroutine(url):
    http_client = AsyncHTTPClient()
    respone = yield http_client.fetch(url)
    raise gen.Return(response.body)


#print syncronous_fetch('http://www.baidu.com')
#print async_fetch_future('www.baidu.com')
#print fetch_coroutine('http://www.baidu.com')

@gen.coroutine
def divide(x, y):
    return x/y

def bad_call():
    divide(1,0)

@gen.coroutine
def good_call():
    divide(1, 0)
