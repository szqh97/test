#!/usr/bin/env python
import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import tornado.httpclient


from tornado.options import define, options
define('port', default = 8000, help = 'run on the gvien port', type = int)

class IndexHandler(tornado.web.RequestHandler):
    def get(self):
        client = tornado.httpclient.HTTPClient()
        response = client.fetch('http://demo.pythoner.com/itt2zh/ch5.html')
#        response = client.fetch('http://search.twitter.com/search.json?' + 
#                urllib.urlencode({'q':query, 'result_type':'recent', 'rpp':100}))
#        body = json.loads(response.body)
#        result_count = len(body['results'])
#        now = datetime.datetime.utcnow()
#        raw_old_tweet_at = body['results'][-1]['create_at']
#        oldest_tweet_at = datetime.datetime.strptime(raw_old_tweet_at, '%a, %d %b %Y %H:%M:%S +000')
#        secondes_diff = time.mktime(now.timetuple()) - time.mktime(oldest_tweet_at.timetuple())
#        tweets_per_second = float(result_count)/seconds_diff
#        info_template = '''
#        <div style="text-align:centeor">
#            <div style="font-size: 72px">%s</div>
#            <div style="font-size: 144px">%.02f</div>
#            <div style="font-size: 24px">tweets per second</div>
#        </div>
#        '''
#        self.write(info_template % (query, tweets_per_second))
        self.write("the code is %d " % response.code)

Handlers = [
        (r'/', IndexHandler)
        ]
if __name__ == '__main__':
    tornado.options.parse_command_line()
    app = tornado.web.Application(handlers = Handlers)
    http_server = tornado.httpserver.HTTPServer(app)
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()

                
