import textwrap

import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web

from tornado.options import define, options
define('port', default=8888, help = 'run on the given port', type = int)

class ReverseHandler(tornado.web.RequestHandler):
    def get(self, input):
        self.write(input[::-1])

class FrobHandler(tornado.web.RequestHandler):
    def head(self, frob_id):
        frob = None
        if frob is not None:
            self.set_status(200)
        else:
            self.set_status(404)
    def get(self, frob_id):
        frob = retrieve_from_db(frob_id)
        self.write(frob.serialize())

class Wraphandler(tornado.web.RequestHandler):
    def post(self):
        text = self.get_argument('text')
        width = self.get_argument('width', 40)
        self.set_status(404)
        self.write(textwrap.fill(text, int(width)))

handlers = [
        (r'/reverse/(\w+)',ReverseHandler),
        (r'/wrap', Wraphandler)
        ]

if __name__ == '__main__':
    tornado.options.parse_command_line()
    app = tornado.web.Application(handlers = handlers)
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()
