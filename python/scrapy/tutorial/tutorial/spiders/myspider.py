import scrapy
from scrapy import log
from tutorial.items import MyItem
from scrapy.contrib.loader import ItemLoader
class Myspider(scrapy.Spider):
    name = "myspider"
    allowed_domains = ['douban.com']
    def __init__(self, category=None, *args, **kwargs):
        super(Myspider, self).__init__(*args, **kwargs)
        self.allowed_domains = ['douban.com']
        self.start_urls = ['http://music.douban.com/programmes/',
            ]

#    def parse(self, response):
#        self.log('xxxxxxxxxxxxxxxxxx the response url is : %s' % response.url)
#        sel = scrapy.Selector(response)
#        for title in response.xpath('''//div[@class="carousel"]/div[@class="songlist-slides slide-page"]/ul[@class="list-songlist slide-item"]/li[@class="songlist-item"]/a[@class="lnk-songlist"]/@title''').extract():
#            yield MyItem(title=title)
#        for url in response.xpath('''//div[@class="carousel"]/div[@class="songlist-slides slide-page"]/ul[@class="list-songlist slide-item"]/li[@class="songlist-item"]/a[@class="lnk-songlist"]/@href''').extract():
#            yield scrapy.Request(url, callback=self.parse)

    def parse(self, response):
        l = ItemLoader(item = MyItem(), response = response)
        l.add_xpath ('title', '''//div[@class="carousel"]/div[@class="songlist-slides slide-page"]/ul[@class="list-songlist slide-item"]/li[@class="songlist-item"]/a[@class="lnk-songlist"]/@title''')
        return l.load_item()
