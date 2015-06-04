#!/usr/bin/env python
import tornado.httpserver
import tornado.ioloop
import tornado.web
from tornado import gen

class TextHandler(tornado.web.RequestHandler):
    @tornado.web.asynchronous
    def get(self):
        self.generator = self.gen_text(100000)
        tornado.ioloop.IOLoop.instance().add_callback(self.loop)
    def loop(self):
        try: 
            text = self.generator.next()
            self.write(text)
            tornado.ioloop.IOLoop.instance().add_callback(self.loop)
        except StopIteration:
            self.finish()
    
    def gen_text(self, n):
        for x in xrange(n):
            if not x %16:
                yield 'fizzBuzz\n'
            elif not x % 5:
                yield 'Buzz\n'
            elif not x % 3:
                yield 'Fizz\n'
            else:
                yield "%s\n" % x

if __name__ == '__main__':
    application = tornado.web.Application([(r'/text/', TextHandler),])
    http_server = tornado.httpserver.HTTPServer(application)
    http_server.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
