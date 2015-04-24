#!/usr/bin/env python
# -*- coding: utf-8 -*-
import bs4
from scrapy import log
from scrapy.selector import Selector
from scrapy.spider import Spider
from scrapy.http import Request
from scrapy.contrib.loader import ItemLoader
from douban.items import DoubanBookItem, DoubanLinkItem

class DoubanBookSpider(Spider):
    name = 'doubanBook'
    allowed_domains = ['douban.com']
    start_urls = ['http://book.douban.com',
            ]
    def __init__(self, **kwargs):
        super(DoubanBookSpider, self).__init__(self, **kwargs)
        #self.crawler.stats.set_value('crawled_page', 0)
        pass
    def __str__(self):
        return 'DoubanBookSpider'

    def parse_item(self, response):
        book = ItemLoader(item = DoubanBookItem(), response = response)
        
    def parse_page(self, response):

        items = []
        sel = Selector(response)
        sites = sel.xpath('//div[@class="section ebook-area"]//ul[@class="list-col list-col5"]/li//div[@class="title"]')
        for site in sites:
            linkpage = ItemLoader(DoubanLinkItem, response = response)
            title = site.xpath('a/@title').extract()
            link = site.xpath('a/@href').extract()
            title,link = title[0], link[0]
            print title, link 
            linkpage.add_value('title', title)
            linkpage.add_value('pageuri', link)
            items.append(linkpage.load_item())
        return items

    def parse_(self, response):
        return self.parse_page(response)
    def parse(self, response):
        sel = Selector(response)
        sites = sel.xpath('//div[@class="section ebook-area"]//ul[@class="list-col list-col5"]/li//div[@class="title"]')
        for site in sites:
            title = site.xpath('a/@title').extract()
            link = site.xpath('a/@href').extract()
            log.msg(title)
            #print title, link 
            title,link = title[0], link[0]
            self.crawler.stats.inc_value('crawled_page')
            yield Request(url = link, callback=self.parse2)
        log.msg("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")
        log.msg("the crawled page is %s" %(str(self.crawler.stats.get_value('crawled_page')),))
        log.msg("%s" % str(self.crawler.stats.get_stats()))

    def print_linkuri(self, response):
        print  'uri is: ', response.url

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
            log.msg(item['title'].encode('utf-8'))
            log.msg(item['author'].encode('utf-8'))
            return item
