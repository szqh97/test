#!/usr/bin/env python
import httplib2
import os
import threading
import urllib
from urlparse import urlparse, urljoin
from BeautifulSoup import BeautifulSoup

class Singleton(object):
    def __new__(cls):
        if not hasattr(cls, "instance"):
            cls.instance = super(Singleton, cls).__new__(cls)
        return cls.instance

class ImageDownloaderThread(threading.Thread):
    """ A thread for downloading image in parallel. """
    def __init__(self, thread_id, name, counter):
        threading.Thread.__init__(self)
        self.name = name

    def run(self):
        print "Starting thread ", self.name
        download_images(self.name)
        print "Finished thread ", self.name

def travers_site(max_links = 10):
    link_parser_singleton = Singleton()

    # While we have pages to parse in queue
    while link_parser_singleton.queue_to_parse:
        # If collected enough links to download images, return 
        if len(link_parser_singleton.to_visit) == max_links:
            return

        url = link_parser_singleton.queue_to_parse.pop()

        http = httplib2.Http()
        try:
            status, response = http.request(url)
        except Exception:
            continue
        
        # Skip if not a web page
        if status.get("content-type") != 'text/html':
            continue
        
        # Add the link to queue for downloading images
        link_parser_singleton.to_visit.add(url)
        print 'Added', url, 'to queue'

        bs = BeautifulSoup(response)
        
        for link in BeautifulSoup.findAll(bs, 'a'):
            link_url = link.get('href')

        # <img> tag may not contain href attribute
        if not link_url:
            continue

        parsed = urlparse(link_url)

        #If link follows to external web page skip it 
        if parsed.netloc and parsed.netloc != parsed_root.netloc:
            continue

        # COnstruct a full url from a link which can be relative
        link_url = (parsed.scheme or parsed_root.scheme) + "://" + \
            (parsed.netloc or parsed_root.netloc) + parsed.path or ''
        
        # If link was added previously, skip it 
        if link_url in  link_parser_singleton.to_visit:
            continue
        
        #Add a link for further parsing
        link_parser_singleton.queue_to_parse = [link_url] + link_parser_singleton.queue_to_parse

def download_images(thread_name):
    singleton = Singleton()
    # While we have pages where we have not download images
    while singleton.to_visit:
        url = singleton.to_visit.pop()

        http = httplib2.Http()
        print thread_name, "Starting downloading images from ", url
        try:
            status, response = http.request(url)
        except Exception:
            continue
        bs = BeautifulSoup(response)

        #Find all <image tags
        images = BeautifulSoup.findAll(bs, "img")

        for image in images:
            #Get image source url which can be absolute or relative
            src = image.get("src")
            # Construct a full url. if the image url is relative
            # it will be prepended with webpage domain
            # If the image url is absolute, it will remain as is
            src = urljoin(url, src)

            #Get a bsenaem, for example 'image.png' to name file locally
            basename = os.path.basename(src)

            if src not in singleton.downloaded:
                singleton.downloaded.add(src)
                print 'Downloading', src
                #Download image to local file system
                urllib.urlretrieve(src, os.path.join('images', basename))
        print thread_name, "finished downloading images from", url
    
if __name__ == '__main__':
    root = 'http://www.mnsfz.com/'
    parsed_root = urlparse(root)

    singleton = Singleton()
    singleton.queue_to_parse = [root]

    #A set of urls to download images from 
    singleton.to_visit = set()
    #download images
    singleton.downloaded = set()

    travers_site()

    # Create images directory if not exists
    if not os.path.exists('images'):
        os.makedirs('images')

    #Create new threads
    t1 = ImageDownloaderThread(1, "thread-1", 1)
    t2 = ImageDownloaderThread(2, "thread-1", 2)

    #start new threads
    t1.start()
    t2.start()
