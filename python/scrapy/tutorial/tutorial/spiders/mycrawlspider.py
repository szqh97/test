import scrapy
from scrapy.contrib.linkextractors import LinkExtractor
from scrapy.contrib.spiders import CrawlSpider, Rule

#from tutorial.items import ${ProjectName}Item
from tutorial.items import MyItem


class MyCrawlSpider(CrawlSpider):
    name = 'mycrawlspider'
    allowed_domains = ['douban.com']
    start_urls = ['http://music.douban.com/']

    rules = (
        Rule(LinkExtractor(allow=r'programmes/'), callback='parse_item', follow=True),
    )

    def parse_item(self, response):
        items = []
        for it in response.xpath('''//div[@class="carousel"]/div[@class="songlist-slides slide-page"]/ul[@class="list-songlist slide-item"]/li[@class="songlist-item"]/a'''):
            i = MyItem()
            i['title'] = it.xpath('''@title''')[0].extract()
            i['url'] = it.xpath('''@href''')[0].extract()
            items.append(i)
        return items
