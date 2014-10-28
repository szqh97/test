# -*- coding: utf-8 -*-

# Scrapy settings for tutorial project
#
# For simplicity, this file contains only the most important settings by
# default. All the other settings are documented here:
#
#     http://doc.scrapy.org/en/latest/topics/settings.html
#
import scrapy

BOT_NAME = 'tutorial'

SPIDER_MODULES = ['tutorial.spiders']
NEWSPIDER_MODULE = 'tutorial.spiders'
ITEM_PIPELINES = {'tutorial.pipelines.TutorialPipeline':300,
        'tutorial.pipelines.JsonWriterPipeline':800,}
#LOG_LEVEL = scrapy.log.INFO
#STATS_CLASS = 'scrapy.statscol.DummyStatsCollector'
STATS_CLASS = 'scrapy.statscol.MemoryStatsCollector'

# Crawl responsibly by identifying yourself (and your website) on the user-agent
#USER_AGENT = 'tutorial (+http://www.yourdomain.com)'
