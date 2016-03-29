#!/usr/bin/env python
# -*- coding': 'utf-8 -*-
import httplib2
from bs4 import BeautifulSoup

headers = {
    'Host': 'wuximarathon.com',
    'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:37.0) Gecko/20100101 Firefox/37.0',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
    'Accept-Language': 'en-US,en;q=0.5',
    'Referer': 'http://wuximarathon.com/score/report',
    'Cookie': 'Hm_lvt_8a87b3571ffba32424cdd0cf2b1f9958=1458692697,1458693568,1458877896; PHPSESSID=9g6cl160hpkjm474kr4vf0hqo4; fixlogin=1; Hm_lpvt_8a87b3571ffba32424cdd0cf2b1f9958=1458885821',
    'Connection': 'keep-alive'
}
