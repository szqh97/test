#!/usr/bin/env python
import base64
import string
import urllib
import httplib2
import json
import logging
import sys
import os

log = logging.getLogger('youku_parser')
formatter = logging.Formatter('%(threadName)s %(asctime)s %(name)-15s %(levelname)-8s: %(message)s\n')
file_handler = logging.FileHandler('/tmp/youku_parser.log')
file_handler.setFormatter(formatter)
stdout_stream = logging.StreamHandler(sys.stdout)
log.addHandler(file_handler)
log.addHandler(stdout_stream)
log.setLevel(logging.DEBUG)

def F(value, c):
    '''
    value='b4eto0b4'
    c = [19,1,4,7,30,14,28,8,24,17,6,35,34,16,9,10,13,22,32,29,31,21,18,3,2,23,25,27,11,20,5,15,12,0,33,26]

    '''
    a = value
    b = []
    i = 0
    for f in xrange(len(a)):
        e = 0
        for e in xrange(36):
            if ord('a') <= ord(a[f]) and ord('z') >= ord(a[f]):
                i = ord(a[f]) - 97
            else:
                i = string.atoi(a[f]) + 26
            if c[e] == i:
                i = e
                break
        if 25 < i:
            tmp_ch = "%d" %(i-26,)
            b.append(tmp_ch[0])
        else:
            b.append(chr(i + 97))

    return ''.join((b))


def E(a, cc):
    '''
    '''
    e = list()
    c = cc
    value = a
    h = 0; i = 0; f = 0
    b = list(xrange(256))
    for h in xrange(256):
        f = (f + b[h] + ord(value[h % len(value)])) % 256
        b[f], b[h] = b[h], b[f]

    h = 0; f = 0
    for q in xrange(len(c)):
        h = (h + 1) % 256
        f = (f + b[h]) % 256
        b[h], b[f] = b[f], b[h]
        e.append(chr(ord(c[q]) ^ b[(b[h] + b[f]) % 256]))

    return ''.join(e)


def na(value):
    h = [ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53,
            54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2,
            3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
            22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32,
            33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
            50, 51, -1, -1, -1, -1, -1]

    i = len(value)
    a = value
    f = 0; c = 0; b = 0
    e = list()

    while f < i:
        while True:
            c = h[ord(a[f]) & 255]
            f +=1
            if not (f < i and -1 == c):
                break
        if c == -1 :
            break
        while True:
            if f >= i:
                b = 0
            else:
                b = h[ord(a[f]) & 255]
                f += 1
            if not (f < i and -1 == b):
                break
        if -1 == b:
            break
      
        e.append(chr(c << 2 | (b & 48) >> 4))

        while True:
            if f >= i:
                c = 0
            else:
                c = ord(a[f]) & 255
                f += 1
            if c == 61:
                return ''.join(e)
            c = h[c]
            if not (f < i and -1 ==c):
                break
        if -1 == c:
            break

        e.append(chr((b & 15) << 4 | (c & 60) >> 2))

        while True:
            if f >= i:
                b = 0
            else:
                b = ord(a[f] ) & 255
                f += 1
            if 61 == b:
                return ''.join(e)
            b = h[b]
            if not (f < i and -1 == b):
                break
        if -1 == b:
            break
        e.append(chr((c & 3) << 6 |b))
    return ''.join(e)

def encoder(a, c, isToBase64):
    bytesR = list()
    f = 0; h = 0; q = 0
    b = list(xrange(256))
    while h < 256:
        f = (f + b[h] + ord(a[h % len(a)])) % 256
        b[h], b[f] = b[f], b[h]
        h+=1
    
    f = 0; h = 0; q = 0
    while q < len(c):
        h = (h + 1) % 256
        f = (f + b[h]) % 256
        b[h], b[f] = b[f], b[h]
        bytesR.append(chr(ord(c[q]) ^ b[(b[h] + b[f]) % 256]))
        q += 1
    result = ''.join(bytesR)

    if isToBase64:
        return base64.b64encode(result)
    return result


def gen_new_ep(vid, ep):
    template1 = 'becaf9be'
    template2 = 'bf7e5f01'
    _decode_ep = base64.b64decode(ep)
    t_s_slice = encoder(template1, _decode_ep, False)
    sid, token = t_s_slice.split('_')
    whole = '{0}_{1}_{2}'.format(sid, vid, token)
    new_ep = encoder(template2, whole, True)

    return new_ep, sid, token


def get_m3u8_url(vid, media_type = 'flv'):
    type_dict = {'hd3':'flv', 'hd2':'flv', 'mp4':'flv', 'flvhd':'flv', '3gphd':'3gp', 'flv':'flv'}
    get_video_data_url = 'http://v.youku.com/player/getPlayList/VideoIDS/{0}/Pf/4/ctype/12/ev/1'.format(vid)
    m3u8_template = 'http://pl.youku.com/playlist/m3u8?ctype=12&ep={0}&ev=1&keyframe=1&oip={1}&sid={2}&token={3}&type={4}&vid={5}'
    http = httplib2.Http(disable_ssl_certificate_validation=False)
    resp, body = http.request(get_video_data_url)
    #logging.info(get_video_data_url)
    data_json = None
    if resp.status == 200:
        data_json = json.loads(body)
    else:
        log.error('request to {0} error, status is {1}'.format(get_video_data_url, resp.status))
        return None
    data_0 = data_json.get('data')[0]
    oip = data_0.get('ip')
    ep = data_0.get('ep')
    segs = data_0.get('segs')
    title = data_0.get('title')

    if segs.get('flv'):
        media_type = 'flv'
    elif segs.get('hd3'):
        media_type = 'hd3'
    elif segs.get('hd2'):
        media_type = 'hd2'
    elif segs.get('mp4'):
        media_type = 'mp4'

    new_ep, sid, token = gen_new_ep(vid, ep)
    ep = urllib.quote(new_ep)
    m3u8_url = m3u8_template.format(ep, oip, sid, token, media_type, vid)
    #log.info('the m3u8 url is {0} . '.format(m3u8_url))

    return m3u8_url, title, type_dict.get(media_type)

vid = sys.argv[1]
m3u8, t, s = get_m3u8_url(vid)
print m3u8
