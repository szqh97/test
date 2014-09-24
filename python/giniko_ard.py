#!/usr/bin/env python
import httplib2


headers = {
        'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
        'Accept-Encoding': 'gzip, deflate', 
        'Accept-Language': 'en-US,en;q=0.5',
        'Connection': 'keep-alive',
        'Cookie' : '__utma=52549950.1896136233.1409734827.1411458890.1411461214.17; __utmz=52549950.1410859242.8.2.utmcsr=billing.giniko.com|utmccn=(referral)|utmcmd=referral|utmcct=/; __utmc=52549950; __utmb=52549950.31.10.1411461214; PHPSESSID=m639bkisnm3e97m5sq726pis65',
        'Host': 'nimplus1.giniko.com',
        'Referer': 'http://www.giniko.com/dvr/jwplayer/jwplayer.flash.swf',
        'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:30.0) Gecko/20100101 Firefox/30.0'
    }
url = 'http://nimplus1.giniko.com/daserste/daserste.stream/playlist.m3u8'
http = httplib2.Http()
response, xml_stream = http.request(url, 'GET')
print url.replace('playlist.m3u8', xml_stream.split('\n')[-2].split('?')[0])


