#!/usr/bin/env python
import urllib2
import BeautifulSoup
import traceback
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
    all_barnds_page_list = {}
    #products_page_list = {}
    for category, url in categories2_list.iteritems():
        res = urllib2.urlopen(url)
        html = res.read()
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
            print category, url
            print traceback.format_exc()

    return brands_list

def get_a_brand_spots(brand, brand_url):

    print "get_a_brand_spots ...", brand_url

    soup = None
    spots_list = {}
    res = urllib2.urlopen(brand_url)
    html = res.read()
    pos = html.find("Show all Commercials")

    # if you can view all commercials
    if pos != -1:
        res = urllib2.urlopen(brand_url + "?view-all=true")
        html = res.read()
    else:
        soup = BeautifulSoup.BeautifulSoup(html)
        clearfix = soup.find("div", {"class":"clearfix"})
        divs = clearfix.findAll("div")
        for d in divs:
            if d.a:
                spot = brand + "/" + d.a.text
                spot_url = home + d.a.get("href")
                spots_list.update({spot:spot_url})

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
    return spots_list

def get_all_spots(brand_list):
    print "get_all_spots ...."
    all_spots = {}
    for category, url in brand_list.iteritems():
        spots = get_a_brand_spots(category, url)
        all_spots.update(spots)
    return all_spots



if __name__ == '__main__':
#    soup = get_browse(browseurl)
#    print "a"
#    c1 = get_tv_ad_categories1(soup)
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
    all_brands = None
    with file ('all_brands.pk', 'r') as f:
        all_brands = cPickle.load(f)
    all_spots = get_all_spots(all_brands)

    with file ('all_spots.pk', 'w') as f:
        cPickle.dump(all_spots, f)
    





