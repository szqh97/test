import tornado.httpserver
import tornado.ioloop
import tornado.web
import tornado.options

from tornado.options import define, options

define('port', default = 8000, help = 'run on the given port', type =int)

class IndexHandler(tornado.web.RequestHandler):
    def get(self):
        greeting = self.get_argument('greeting', 'hello')
        self.write(greeting + ', friendly user')

handlers = [
        (r'/', IndexHandler)
        ]

if __name__ == '__main__':
    tornado.options.parse_command_line()
    #app = tornado.web.Application(handlers = [(r"/", IndexHandler)])
    app = tornado.web.Application(handlers = handlers)
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()

