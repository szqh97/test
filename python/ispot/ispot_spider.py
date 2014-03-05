#!/usr/bin/env python
import os
import urllib2
import BeautifulSoup
import time
import traceback
import logging
import logging.config
import cPickle
logger = logging
def install_logger():
    global logger
    
    logger.config.fileConfig("./logging.conf")
    logger = logger.getLogger("ispot")
install_logger()


spots_file = "./all_spots_url.txt"

home = "http://www.ispot.tv"
browseurl = "http://www.ispot.tv/browse"
retry_times = 5

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

def get_tv_ad_categories1(soup):

    # categories1_list is like {u'Travel': u'http://www.ispot.tv/browse/5/travel', ...}
    spl = soup.body.find('div',{"class":"span3 pull-left"})
    alldivs = spl.div.findAll('div', {"class":"span3"})
    for d in alldivs:
        if d.h2 and d.h2.text == 'TV Ad Categories':
            i = alldivs.index(d)
            alldivs = alldivs[i+1:]
            break
    categories1_list = {}
    for d in alldivs:
        categories1_list.update({d.a.text : home + d.a['href']})
    return categories1_list

def get_tv_ad_categories2(categories1_list):

    #categories2_list is like  {u'Travel/Hotels & Motels': u'http://www.ispot.tv/browse/5.Yy/travel/hotels-and-motels', ...}
    categories2_list = {}
    for category, url in categories1_list.iteritems():
        soup = get_browse(url)
        spl = soup.body.find('div',{"class":"span3 pull-left"})
        alldivs = spl.div.findAll('div', {"class":"span3"})
        for d in alldivs:
            categories2_list.update({'/'.join((category, d.a.text)) : home + d.a['href']})

    return categories2_list

def get_last_categories(categories2_list):
    all_barnds_page_list = {}
    #products_page_list = {}
    for category, url in categories2_list.iteritems():
        #res = urlopen_wrap(url)
        #html = res.read()
        html = get_html(url)
        pos = html.find('Product Categories')

        # current page can find all brands
        if pos == -1:
            all_barnds_page_list.update({category : url + "?view-all=true"})
#        else:
#            soup = BeautifulSoup.BeautifulSoup(html)
#            spl = soup.body.find('div',{"class":"span3 pull-left"})
#            alldivs = spl.div.findAll('div', {"class":"span3"})
#            for d in alldivs:
#                if d.h2 and d.h2.text == 'Product Categories':
#                    i = alldivs.index(d)
#                    alldivs = alldivs[i+1:]
#                    break
#            for d in alldivs:
#                products_page_list.update({'/'.join((category, d.a.text)): home + d.a['href']})
    return all_barnds_page_list

def get_brands(brands_page_list):

    brands_list = {}
    for category, url in brands_page_list.iteritems():
        soup = get_browse(url)
        spl = soup.body.find('div',{"class":"span3 pull-left"})
        alldivs = spl.div.findAll('div', {"class":"span3"})
        alldivs = alldivs[1:]
        try:
            for d in alldivs:
                brands_list.update({'/'.join((category, d.a.text)): home + d.a['href']})
        except Exception, err:
            logger.error("%s, %s", category, url)
            logger.error("get brands error:%s, ", str(traceback.format_exc()))

    return brands_list

def get_a_brand_spots(brand, brand_url):

    logger.info("get_a_brand_spots ... %s", brand_url)

    soup = None
    spots_list = {}
    #res = urlopen_wrap(brand_url)
    #html = res.read()
    html = get_html(brand_url)
    pos = html.find("Show all Commercials")

    # if you can view all commercials
    if pos != -1:
        #res = urlopen_wrap(brand_url + "?view-all=true")
        #html = res.read()
        html = get_html(brand_url + "?view-all=true")
    else:
        soup = BeautifulSoup.BeautifulSoup(html)
        clearfix = soup.find("div", {"class":"clearfix"})
        divs = clearfix.findAll("div")
        for d in divs:
            if d.a:
                spot = brand + "/" + d.a.text
                spot_url = home + d.a.get("href")
                spots_list.update({spot:spot_url})
                with file (spots_file, 'a') as f:
                    spot_info = spot + u" | " + spot_url + "\n"
                    if spot_info.__class__ == unicode:
                        spot_info = spot_info.encode('utf-8')
                    f.write(spot_info)

    if not soup:
        soup = BeautifulSoup.BeautifulSoup(html)
    span2s = soup.findAll("div", {"class":"span2"})
    for d in span2s:
        if d.a:
            href = d.a.get("href")
            if href:
                spot = brand + "/" + d.a.text
                spot_url = home + href
                spots_list.update({spot:spot_url})
                with file(spots_file, 'a') as f:
                    spot_info = spot + u" | " + spot_url + "\n"
                    if spot_info.__class__ == unicode:
                        spot_info = spot_info.encode('utf-8')
                    f.write(spot_info)

    return spots_list

def get_all_spots(brand_list):
    logger.info("get_all_spots ....")
    all_spots = {}
    for category, url in brand_list.iteritems():
        spots = get_a_brand_spots(category, url)
        all_spots.update(spots)
        with file( 'tmp_all_spots.pk', 'w') as f :
            cPickle.dump(all_spots, f)
    return all_spots



if __name__ == '__main__':
    soup = get_browse(browseurl)
    "a"
    c1 = get_tv_ad_categories1(soup)
    with file('industries.pk', 'w') as f:
        cPickle.dump(c1, f)
#    print c1
#    c2 = get_tv_ad_categories2(c1)
#    print len(c2)
#    print c2
#    all_brands_page = get_last_categories(c2)
#    with file('all_brands_page.pk', 'w') as f:
#        cPickle.dump(all_brands_page, f)
#    with file ('all_brands_page.pk', 'r') as f:
#        all_brands_page_list = cPickle.load(f)
#    all_brands = get_brands(all_brands_page_list)
#    with file ('all_brands.pk', 'w') as p:
#        cPickle.dump(all_brands, p)
#    all_brands = None
#    with file ('all_brands.pk', 'r') as f:
#        all_brands = cPickle.load(f)
#    all_spots = get_all_spots(all_brands)
#
#    with file ('all_spots.pk', 'w') as f:
#        cPickle.dump(all_spots, f)
#    logger.info("complete ...")
    





