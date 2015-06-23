#!/usr/bin/env python
import html2csv
import httplib2
import urllib

db = 'tarcker2'
cookie = 'JSESSIONID=xdlriq415dfi1xev9wd4n98xt'
sql = 'select coutn(*), id, company_id from  matchedVideo LIMIT 5;'

def get_cookie():
    get_cookie_url = 'http://206.99.94.148:9090/web/login.html'
    headers = {
        'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:30.0) Gecko/20100101 Firefox/30.0',
        'Referer': 'http://206.99.94.148:9090/web/db',
        'Connection': 'keep-alive'
    }
    http = httplib2.Http(disable_ssl_certificate_validation=True)
    res, body =  http.request('GET', headers = headers)


def query_db(cookie, db, sql):
    args = {
            'db':db,
            'sql': sql,
            }
    url  = 'http://206.99.94.148:9090/web/db?action=query'
    headers = {
    'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:30.0) Gecko/20100101 Firefox/30.0',
    'Accept-Language': 'en-US,en;q=0.5',
    'Accept-Encoding': 'gzip, deflate',
    'Cookie': cookie,
    'Connection': 'keep-alive'
    }
    post_data = urllib.urlencode(args)
    http = httplib2.Http(disable_ssl_certificate_validation=True)
    resp, body = http.request('POST', headers =headers, body = post_data)
    print resp, body

query_db(cookie, db, sql)

    




        

