import tornado
import tornado.ioloop
import tornado.web
import os, uuid
import tempfile

__UPLOADS__ = "/home/li_yun/uploads/"

class Userform(tornado.web.RequestHandler):
    def get(self):
        print 'Userform'
        self.render("postfiles.html")
@tornado.web.stream_request_body 
class PostFilesHandler(tornado.web.RequestHandler): 
    def post(self): 
        print self.request
        pass
        for postfile in self.request.files: 
            print("File info:",postfile) # There is no postfile["body"] here!!! 
    def prepare(self): 
        self.temp_file = tempfile.NamedTemporaryFile(delete=False) 
    def data_received(self, chunk): 
        self.temp_file.write(chunk) # This is great but which file is this???



class Upload(tornado.web.RequestHandler):
    def post(self):
        fileinfo = self.request.files['filearg'][0]
        fname = fileinfo['filename']
        extn = os.path.splitext(fname)[1]
        cname = str(uuid.uuid4()) + extn
        fh = open(__UPLOADS__ + cname, 'w')
        fh.write(fileinfo['body'])
        self.finish(cname + " is uploaded!! Check %s folder" %__UPLOADS__)


application = tornado.web.Application([
        (r"/", Userform),
        (r"/upload", Upload),
        (r'/postfiles', PostFilesHandler),
        ], debug=True)


if __name__ == "__main__":
    application.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
