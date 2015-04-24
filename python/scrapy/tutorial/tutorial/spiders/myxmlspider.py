# -*- coding: utf-8 -*-
from scrapy import log
from scrapy.contrib.spiders import XMLFeedSpider

#from $project_name.items import ${ProjectName}Item
from tutorial.items import MyItem


class MyXmlSpider(XMLFeedSpider):
    name = 'myxmlspider'
    allowed_domains = ['douban.com']
    start_urls = ['http://music.douban.com/']
    iterator = 'iternodes' # you can change this; see the docs
    itertag = 'item' # change it accordingly


    def parse_node(self, response, selector):
        log.msg('the url =========== %s ' % response.url)
        items = []
        for it in response.xpath('''//div[@class="carousel"]/div[@class="songlist-slides slide-page"]/ul[@class="list-songlist slide-item"]/li[@class="songlist-item"]/a'''):
            i = MyItem()
            i['title'] = it.xpath('''@title''')[0].extract()
            i['url'] = it.xpath('''@href''')[0].extract()
            items.append(i)
        return items
        #i['url'] = selector.select('url').extract()
        #i['name'] = selector.select('name').extract()
        #i['description'] = selector.select('description').extract()
