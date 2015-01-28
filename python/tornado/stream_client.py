# 
# Test of experimental Tornado feature for a streaming request body handler, see
# https://github.com/nephics/tornado/commit/1bd964488926aac9ef6b52170d5bec76b36df8a6
#

#
#  Client sending file to server
#

import tornado.httpclient as httpclient

with open('test.pdf', 'r') as f:
    body = f.read()

http_client = httpclient.HTTPClient()
request = httpclient.HTTPRequest('http://localhost:8888', 'POST', body=body,
                                 headers={'Content-Type': 'application/pdf'})
try:
    response = http_client.fetch(request)
    print('File uploaded, server response: {0}'.format(response.body))
except httpclient.HTTPError, e:
    print "Error:", e
