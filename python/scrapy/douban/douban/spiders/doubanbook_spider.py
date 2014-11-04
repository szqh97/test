#!/usr/bin/env python
# -*- coding: utf-8 -*-
import bs4
from scrapy.selector import Selector
from scrapy.spider import Spider
from scrapy import log
from scrapy.http import Request
from douban.items import DoubanBookItem

class DoubanBookSpider(Spider):
    name = 'doubanBook'
    allowed_domains = ['douban.com']
    start_urls = ['http://book.douban.com',
            ]
    def parse(self, response):
        self.log('xxxxxxxxxxxxx')
        sel = Selector(response)
        sites = sel.xpath('//div[@class="section ebook-area"]//ul[@class="list-col list-col5"]/li//div[@class="title"]')
        for site in sites:
            title = site.xpath('a/@title').extract()
            link = site.xpath('a/@href').extract()
            title,link = title[0], link[0]
            print title, link 
            yield Request(url = link, callback=self.parse2)

    def parse2(self, response):
        soup = bs4.BeautifulSoup(response.body)
        bookInfo = soup.find('div', {'class':'article-profile-section article-profile-primary'})
        if bookInfo:
            item = DoubanBookItem()
            item['author'] = "".join(bookInfo.find('span',{'itemprop':'author'}).contents[0])
            item['title'] = "".join(bookInfo.find('h1', {'class':'article-title'}).contents[0])
            item['category'] = "".join(bookInfo.find('span', {'itemprop':'genre'}).contents[0])
            item['price']= bookInfo.find('a', {'class':'btn login purchase btn-icon'}).findAll('span')[-1].contents[0]
                
            # debug
            print item['title'].encode('utf-8')
            print item['author'].encode('utf-8')
            return item
