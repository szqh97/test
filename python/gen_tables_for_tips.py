#!/usr/bin/env python
import sys


from BeautifulSoup import BeautifulSoup

soup = BeautifulSoup(file(sys.argv[1], 'r').read())
tables = soup.findAll('table')

title_bg = ''
discovery_output = ''
di=''
matched_video_sync=''

for t in tables:
    try:
        title_bg = t.find('th',{'class':'title_bg'}).contents[0]
        if title_bg == u'Discovery output':
            discovery_output = str(t)
        if title_bg == u'DI':
            di = str(t)
        if title_bg.find(' Matched Video Sync') == 0:
            matched_video_sync = str(t)
    except Exception, err:
        pass


with file('/tmp/Discovery_output.html', 'w') as f:
    f.write(discovery_output)
with file('/tmp/di.html', 'w') as f:
    f.write(di)
with file('/tmp/matched_video_sync.html', 'w') as f:
    f.write(matched_video_sync)
