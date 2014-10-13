import scrapy
from tutorial.items import DmozItem
from scrapy import log
class DmozSpider(scrapy.Spider):
    name    =   "dmoz"
    allowed_domains = ["dmoz.org"]
    start_urls = [
        "http://www.dmoz.org/Computers/Programming/Languages/Python/Books/",
        "http://www.dmoz.org/Computers/Programming/Languages/Python/Resources/"
    ]

    def parse(self, response):
        items = []
        for sel in response.xpath('//ul/li'):
#            title = sel.xpath('a/text()').extract()
#            link = sel.xpath('a/@href').extract()
#            desc = sel.xpath('text()').extract()
            item = DmozItem()
            item['title'] = sel.xpath('a/text()').extract()
            self.log("the title is %s" % str(item['title']) )
            item['link'] = sel.xpath('a/@href').extract()
            item['desc'] = sel.xpath('text()').extract()
        return items
