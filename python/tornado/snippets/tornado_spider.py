#!/usr/bin/env python
# -*- coding: utf-8 -*-
import time
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
        raise e
