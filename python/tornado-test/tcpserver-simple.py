"""
A simple echo server for telnet, implemented using tornado.gen
"""

import itertools
import socket

import tornado.gen
import tornado.ioloop
import tornado.iostream
import tornado.tcpserver

class SimpleEcho(object):
    """
        Per-connection object.
    """

    def __init__(self, client_id):
        self.client_id = client_id
        self.message_id_alloc = itertools.count(1)
        return

    @tornado.gen.coroutine
    def on_disconnect(self):
        self.log("on_disconnect")
        yield []
        self.log("on_disconnect done")
        return

    @tornado.gen.coroutine
    def dispatch(self):
        try:
            while True:
                self.log("waiting for line on stream {}", self.stream)
                line = yield self.stream.read_until("\n")
                message_id = next(self.message_id_alloc)
                self.log("got line {}: {}", message_id, repr(line))
                yield self.stream.write(line)
        except tornado.iostream.StreamClosedError:
            pass
        return

    @tornado.gen.coroutine
    def on_connect(self):
        self.log("on_connect")
        yield self.dispatch()
        self.log("on_connect done")
        return

    def log(self, msg, *args, **kwargs):
        print "[{}]: {}".format(self.client_id, msg.format(*args, **kwargs))
        return

class SimpleEchoServer(tornado.tcpserver.TCPServer):
    """
        Server listener object.
    """

    def __init__(self, io_loop=None, ssl_options=None, max_buffer_size=None):

        tornado.tcpserver.TCPServer.__init__(self,
            io_loop=io_loop, ssl_options=ssl_options, max_buffer_size=max_buffer_size)

        self.client_id_alloc = itertools.count(1)
        return

    @tornado.gen.coroutine
    def handle_stream(self, stream, address):
        print "begin handle_stream"
        client_id = next(self.client_id_alloc)

        print "got id", client_id

        print "creating conn"
        conn = SimpleEcho(client_id)

        stream.set_close_callback(conn.on_disconnect)
        stream.socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        stream.socket.setsockopt(socket.IPPROTO_TCP, socket.SO_KEEPALIVE, 1)

        conn.stream = stream

        print "yielding to conn.on_connect()"

        yield conn.on_connect()

        print "exiting handle_stream"

        return

if __name__ == "__main__":

    server = SimpleEchoServer()
    server.listen(1234)
    def test_timer():
        import time
        print "ts now is :" + str(time.time())
    
    # test timer worker.
    tornado.ioloop.PeriodicCallback(test_timer, 5000).start()

    tornado.ioloop.IOLoop.instance().start()
