import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import tornado.websocket
import logging

from tornado.options import define, options
define('port', default = 8888, help = 'run on the given port', type = int)
clients = dict()
class IndexHandler(tornado.web.RequestHandler):
    def get(self):
        logging.info('in get ....')
        greeting = self.get_argument('greeting', 'hello')
        #raise tornado.web.HTTPError(400, log_message="{'ErrCode':400, 'ErrMsg':'bad request...'}")
        #self.write(greeting + ', frendly user')
        self.clear()
        self.set_status(400)
        self.finish('tttttttttttttttttttttt')

    def post(self):
        logging.info(self.request.body)
        body = self.get_argument('body', 'there is no body?')
        logging.info(body)
        

class WebSocketHandler(tornado.websocket.WebSocketHandler):
    def open(self, *args):
        
        self.id = self.get_argument('id')
        self.stream.set_nodelay(True)
        clients[self.id] = {'id':self.id, 'object':self}

    def on_message(self, message):
        print 'Client %s received a message: %s' %(self.id, message)

    def on_close(self):
        if self.id in clients:
            del clients[self.id]

handlers = [
        (r'/', IndexHandler),
        (r'/', WebSocketHandler),
        ]


if __name__ == '__main__':
    tornado.options.parse_command_line()
    #app = tornado.web.Application(handlers = [(r'/', IndexHandler)])
    app = tornado.web.Application(handlers = handlers)
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()
