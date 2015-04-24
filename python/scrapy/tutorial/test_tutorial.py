#!/usr/bin/env python
from scrapy.crawler import Crawler
from scrapy.settings import settings
import tutorial.spiders.myspider

runner = Crawler(settings)
runner.crawl(tutorial.spiders.myspider.Myspider())
runner.install()
#runner.start_crawling()
runner.start()

