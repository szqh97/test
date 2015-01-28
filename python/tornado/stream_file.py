# 
# Test of experimental Tornado feature for a streaming request body handler, see
# https://github.com/nephics/tornado/commit/1bd964488926aac9ef6b52170d5bec76b36df8a6
#
#
#  Server with request handler reading of file stream from client
#


import tornado.ioloop
import tornado.web
import uuid
import tempfile

@tornado.web.stream_request_body 
class PostFilesHandler(tornado.web.RequestHandler): 
    def post(self): 
        for postfile in self.request.files: 
            print("File info:",postfile) # There is no postfile["body"] here!!! 
    def prepare(self): 
        self.temp_file = tempfile.NamedTemporaryFile(delete=False) 
    def data_received(self, chunk): 
        self.temp_file.write(chunk) # This is great but which file is this???

@tornado.web.stream_request_body
class StreamingHandler(tornado.web.RequestHandler):
    def initialize(self):
        self.bytes_read = 0

    def prepare(self):
        print self.request
        self.tem_file = file(tempfile.mktemp(prefix='tttt'), 'w')
        #self.tem_file = file('/tmp/tmp5jkOivkkk', 'w')
        self.request.connection.set_max_body_size(99999999999)
        self.request.connection.set_body_timeout(10000)
        pass

    def data_received(self, chunk):
        self.tem_file.write(chunk)
        if self.bytes_read == 0:
            print 'length of chunk is ', len(chunk)
        self.bytes_read += len(chunk)

    def put(self):
        self.write(str(self.bytes_read))
        

@tornado.web.stream_request_body
class MainHandler(tornado.web.RequestHandler):
    def post(self):
        # open a file or a socket to stream the uploaded data to
        self.fp = open('file_{0}'.format(uuid.uuid1().hex), 'w')
        self.request.request_continue()
        self.read_bytes = 0
        self._read_chunk()

    def _read_chunk(self):
        # set the chunk size and read bytes from the stream
        chunk_length = min(10000,
            self.request.content_length - self.read_bytes)
        if chunk_length > 0:
            self.request.connection.stream.read_bytes(
                chunk_length, self._on_chunk)
        else:
            self.fp.close()
            self._on_uploaded()

    def _on_chunk(self, chunk):
        if chunk:
            # write chunk of data to disk
            self.fp.write(chunk)
            self.read_bytes += len(chunk)
        else:
            # no more incoming data, set correct content_length
            self.content_length = self.read_bytes
        self._read_chunk()

    def _on_uploaded(self):
        self.write("Uploaded!")
        self.finish()

if __name__ == "__main__":
    application = tornado.web.Application([
        (r"/", MainHandler),
        (r"/stream", StreamingHandler),
        (r'/postfiles', PostFilesHandler),
    ])
    application.listen(8888)
    tornado.ioloop.IOLoop.instance().start()

