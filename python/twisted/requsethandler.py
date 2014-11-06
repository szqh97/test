#!/usr/bin/env python

from twisted.internet import reactor
from twisted.web import http

class MyRequestHandler(http.Request):
    resources = {

            "/": "<h1>Home</h1>Hmoe Page",
            "/about": "<h1>About</h1>All About me",
    }

    def process(self):
        self.setHeader("Content-type", 'text/html')
        if self.resources.has_key(self.path):
            self.write(self.resources[self.path])
        else:
            self.setResponseCode(http.NOT_FOUND)
            self.write("<h1>Not Found</h1>Sorry, no such resource.")
        self.finish()

class MyHTTP(http.HTTPChannel):
    requestFactory = MyRequestHandler

class MyHTTPFactory(http.HTTPFactory):
    def buildProtocol(self, addr):
        return MyHTTP()
    
reactor.listenTCP(8000, MyHTTPFactory())
reactor.run()

