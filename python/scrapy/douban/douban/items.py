# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy
from scrapy import Field



class DoubanBookItem(scrapy.Item):
    author = Field()
    title = Field()
    category = Field()
    price = Field()

class DoubanLinkItem(scrapy.Item):
    title = Field()
    link = Field()
    


class DoubanItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    pass
