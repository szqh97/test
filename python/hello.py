#!/usr/bin/env python
import web
import Queue

urls = ("/.*", "hello")
cnt = 0

class hello:
    def __init__(self):
        global cnt
        cnt +=1
    def GET(self):
        return 'Hello, world, cnt is %d\n' % (cnt,)

application = web.application(urls, globals()).wsgifunc()
#if __name__ == "__main__":
#    app = web.application(urls, globals())
#    app.run()
