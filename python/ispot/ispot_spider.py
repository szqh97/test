#!/usr/bin/env python
import urllib2
import BeautifulSoup
import cPickle

home = "http://www.ispot.tv"
browseurl = "http://www.ispot.tv/browse"

def get_browse(browseurl):
    try:
        res = urllib2.urlopen(browseurl)
        html = res.read()
        soup = BeautifulSoup.BeautifulSoup(html)
    except Exception, err:
        print traceback.format_exc()
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
    all_barnds_list = {}
    products_page_list = {}
    for category, url in categories2_list.iteritems():
        res = urllib2.urlopen(url)
        html = res.read()
        pos = html.find('Product Categories')

        # current page can find all brands
        if pos == -1:
            all_barnds_list.update({category : url + "?view-all=true"})
        else:
            soup = BeautifulSoup.BeautifulSoup(html)
            spl = soup.body.find('div',{"class":"span3 pull-left"})
            alldivs = spl.div.findAll('div', {"class":"span3"})
            for d in alldivs:
                if d.h2 and d.h2.text == 'Product Categories':
                    i = alldivs.index(d)
                    alldivs = alldivs[i+1:]
                    break
            for d in alldivs:
                products_page_list.update({'/'.join((category, d.a.text)): home + d.a['href']})
    return all_barnds_list, products_page_list

def get_brands(categories_list):
    pass;

if __name__ == '__main__':
    soup = get_browse(browseurl)
    c1 = get_tv_ad_categories1(soup)
    c2 = get_tv_ad_categories2(c1)
    all_brands, products = get_last_categories(c2)
    with file('call_brands.pk', 'w') as f:
        cPickle.dump(all_brands, f)
    with file('products.pk', 'w') as f:
        cPickle.dump(products.f)





