#!/usr/bin/env python
import os
import urllib2
import BeautifulSoup
import time
import traceback
import logging
import logging.config
import cPickle
import sys
logger = logging

def urlopen_wrap(url):
    i = 1
    while True:
    #    if i > retry_times:
    #        raise Exception("Exception: retried several times to connect %S" % url)
        try:
            res = urllib2.urlopen(url)
            return res
        except Exception, err:
            logger.error('retry to connect: %s', url)
            time.sleep(0.5* (2 ** (i-1)))
            i+=1

def get_html(url):
    i = 1
    while True:
        #if i > retry_times:
        #    raise Exception("Exception, get html from: %s, out of time " % url)
        try:
            res = urlopen_wrap(url)
            html = res.read()
            return html
        except Exception, err:
            logger.error("retryed to get html: %s", url) 
            time.sleep(0.5* (2 ** (i-1)))
            i+=1

def get_browse(browseurl):
    try:
        #res = urlopen_wrap(browseurl)
        #html = res.read()
        html = get_html(browseurl)
        soup = BeautifulSoup.BeautifulSoup(html)
    except Exception, err:
        logger.error("get_browe Error%s", str(traceback.format_exc()))
    return soup

def get_img_list(page_url):
    soup = get_browse(page_url)
    imgs = soup.findAll('img')
    home = 'http://www.jiaruxi.com'
    img_list = []
    for img in imgs:
        try:
            img_url = img['big-src']
            img_url = home + img_url
            img_list.append(img_url)
        except Exception, e:
            print 'get big src error'
    return img_list

def down_img(url):
    img_list = get_img_list(url)
    cmd = 'wget -c %s -o %s'
    for img in img_list:
        pic = ''.join(img.split('/')[-2:])
        os.system(cmd % (img, pic))


if __name__ == '__main__':
    down_img(sys.argv[1])
