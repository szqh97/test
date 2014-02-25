#!/usr/bin/env python

import web

import sys, logging
from wsgilog import WsgiLog
import config

class Log(WsgiLog):
    def __init__(self, application):
        WsgiLog.__init__(
            self,
            application,
            logformat = '%(message)s',
            tofile = True,
            file = config.log_file,
            interval = config.log_interval,
            backups = config.log_backups
            )

urls = ("/hello", "hello")
class hello:
    def POST(self):
        data = web.data()
        if data.has_key("qvod_url"):
            print data
    def GET(self):
        data = web.input()
        if data.has_key('a'):
            print data['a']

if __name__ == '__main__':
    app = web.application(urls, globals())
    app.run()


