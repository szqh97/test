#!/usr/bin/env python
import urllib2
import BeautifulSoup
from ispot_spider import *
import cPickle

def get_a_brand_spots(brand, brand_url):

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

    
