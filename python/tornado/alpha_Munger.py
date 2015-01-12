import os.path
import random
import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web

from tornado.options import define, options
define("port", default = 8888, help='run on the given port', type = int)

class IndexHandler(tornado.web.RequestHandler):
    def get(self):
        self.render('munger_index.html')

class TemplateInder(tornado.web.RequestHandler):
    def get(self):
        self.render("template_index.html", header_text="head goes here",
                footer_text = "Footer goes here")

class MungedPageHandler(tornado.web.RequestHandler):
    def map_by_first_letter(self, text):
        mapped = dict()
        for line in text.split('\r\n'):
            for word in [x for x in line.split(' ') if len(x)> 0]:
                if word[0] not in mapped: mapped[word[0]] = []
                mapped[word[0]].append(word)
        return mapped

    def post(self):
        source_text = self.get_argument('source')
        text_to_change = self.get_argument('change')
        source_map = self.map_by_first_letter(source_text)
        change_lines = text_to_change.split('\r\n')
        self.render('munged.html', source_map = source_map, change_lines = change_lines, 
                choice = random.choice)


if __name__ == '__main__':
    tornado.options.parse_command_line()
    handlers = [
            (r'/', IndexHandler),
            (r'/template', TemplateInder),
            (r'/poem', MungedPageHandler)
            ]
    template_path = os.path.join(os.path.dirname(__file__), "templates")
    static_path = os.path.join(os.path.dirname(__file__), "static")
    app = tornado.web.Application(handlers = handlers, template_path = template_path, static_path = static_path, debug=True)
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()
