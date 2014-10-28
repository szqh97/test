# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

from scrapy.exceptions import DropItem
import json

class TutorialPipeline(object):
    def process_item(self, item, spider):
        if item['title'] == '':
            raise DropItem("Missing price")
        else:
            return item

class JsonWriterPipeline(object):
    def __init__(self):
        self.file = open('items.jl', 'wb')
        pass

    def process_item(self, item, spider):
        line = json.dumps(dict(item)) + '\n'
        self.file.write(line)
        return item

