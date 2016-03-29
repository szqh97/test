#!/usr/bin/env python
# -*- coding: utf-8 -*-
import time
from datetime import timedelta
try:
    from HTMLParser import HTMLParser
    from urlparse import urljoin, urldefrag
except ImportError:
    from html.parser import HTMLParser
    from urllib.parse import urljoin, urldefrag
from tornado import httpclient, gen, ioloop, queues
import traceback

base_url = 'http://www.tornadoweb.org/en/stable/'
concurrency = 10


def get_links_from_url(url):
    try:
        response = yield httpclient.AsyncHTTPClient().fetch(url)
        print "fetched %s" % url
        html = response.body if isinstance(response.body, str) \
                else response.body.decode()
        urls = [urljon(url, remove_fragment(new_url)) for new_url in get_links(html)]
    except Exception, e:
        print 'exception is %s\n %s' % (traceback.format_exc(), url)
        raise gen.Return([])

    raise gen.Return(urls)

def remove_fragment(url):
    pure_url, frag = urldefrag(url)
    return pure_url

def get_links(html):
    class URLSeeker(HTMLParser):
        def __init__(self):
            HTMLParser.__init__(self)
            self.urls = []

        def handle_starttag(self, tag, attrs):
            href = dict(attrs).get('href')
            if href and tag == 'a':
                self.urls.append(href)

    url_seeker = URLSeeker()
    url_seeker.feed(html)
    return url_seeker.urls

@gen.coroutine
def main():
    q = queues.Queue()
    start = time.time()
    fetching, fetched = set(), set()

    @gen.coroutine
    def fetch_url():
        current_url = yield q.get()
        try:
            if current_url in fetching:
                return
            print 'fetching %s' % current_url
            fetching.add(current_url)
            urls = yield get_links_from_url(current_url)
            fetched.add(current_url)

            for new_url in urls:
                if new_url.startswith(base_url):
                    yield q.put(new_url)
        except Exception, e:
            print traceback.format_exc()
            raise e
        finally:
            q.task_done()


    @gen.coroutine
    def worker():
        while True:
            yield fetch_url()

    q.put(base_url)

    for _ in range(concurrency):
        worker()
    yield q.join(timeout = timedelta(seconds = 300))
    assert fetching == fetched

    print 'Done in %d seconds, fetched %s URLs.' % ( time.time() - start, len(fetched) )

if __name__ == '__main__':
    import logging
    logging.basicConfig()
    io_loop = ioloop.IOLoop.current()
    io_loop.run_sync(main)
