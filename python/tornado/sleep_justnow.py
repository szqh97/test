#!/bin/env python
import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import tornado.httpclient

import time

from tornado.options import define, options
define('port', default = 8888, help = 'run on the given port', type = int)

class SleepHandler(tornado.web.RequestHandler):
    def get(self):
        time.sleep(5)
        self.write('when I sleep 5s')

class JustNowHandler(tornado.web.RequestHandler):
    def get(self):
        self.write('I hope just now')

if __name__ == '__main__':
    tornado.options.parse_command_line()
    app = tornado.web.Application(handlers = [
        (r'/sleep', SleepHandler),
        (r'/justnow', JustNowHandler)
        ])
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()
