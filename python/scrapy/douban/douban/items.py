# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy
class DoubanBookItem(scrapy.Item):
    title = scrapy.Field()
    author = scrapy.Field()    
    publisher = scrapy.Field()
    category = scrapy.Field()
    price = scrapy.Field()

class DoubanItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    pass
