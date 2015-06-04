#!/usr/bin/env python
import tornado.httpserver
import tornado.web
import tornado.ioloop
import tornado.options
import tornado.httpclient

from tornado.options import define, options
define('port', default = 8000, type = int, help = 'run on the givine port')

class IndexHandler(tornado.web.RequestHandler):
    @tornado.web.asynchronous
    def get(self):
        client = tornado.httpclient.AsyncHTTPClient()
        client.fetch('http://demo.pythoner.com/itt2zh/ch5.html', callback = self.on_response)
        
    def on_response(self, response):
        code = response.code
        self.write('the code is %d' % code)
        self.finish()



handlers = [
        (r'/', IndexHandler)
        ]

if __name__ == '__main__':
    tornado.options.parse_command_line()
    app = tornado.web.Application(handlers = handlers)
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()

