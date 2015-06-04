#!/usr/bin/env python
import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import tornado.httpclient
import tornado.gen


from tornado.options import define, options
define('port', default = 8000, help = 'run on the gvien port', type = int)

class IndexHandler(tornado.web.RequestHandler):
# this is the old way?
#    @tornado.web.asynchronous
#    @tornado.gen.engine
    @tornado.gen.coroutine
    def get(self):
        client = tornado.httpclient.AsyncHTTPClient()
        response = yield tornado.gen.Task(client.fetch, 'http://demo.pythoner.com/itt2zh/ch5.html')
        self.write('the code is %d' % response.code)
        self.finish()

Handlers = [
        (r'/', IndexHandler)
        ]
if __name__ == '__main__':
    tornado.options.parse_command_line()
    app = tornado.web.Application(handlers = Handlers)
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()

 

