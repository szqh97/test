# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

import os
import sys
import json
from scrapy.contrib.exporter import JsonItemExporter, JsonLinesItemExporter
from scrapy.xlib.pydispatch import dispatcher
from scrapy import signals 

class DoubanPipeline(object):
    def open_spider(self, spider):
        print "starting spider" 
        with file('ttt.txt', 'w') as t:
            pass

    def process_item(self, item, spider):
        return item

    def close_spider(self, spider):
        print "closing spider" 

class DoubanJsonWrite(object):
    def __init__(self):
        #dispatcher.connect(self.open_spider, signals.spider_opened)
        #dispatcher.connect(self.close_spider, signals.spider_closed)
        self.itemsfile = open('imtes.jl', 'w')

    def open_spider(self, spider):
        self.exporter = JsonItemExporter(self.itemsfile)
        self.exporter.start_exporting()
    def close_spider(self, spider):
        self.exporter.finish_exporting()


    def process_item(self, item, spider):
        self.exporter.export_item(item)
        return item

