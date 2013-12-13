#!/usr/bin/env python
# -*- coding: utf8 -*-
# Author: li_yun@vobile.cn
# Date: 2013-12-13 22:33:14

import web
import simplejson


urls = (
        "/videocapture", "VideoCapture",
        "/.*", "default",
        )

class VideoCapture:
    def POST(self):
        raw_data = web.data()
        post_data = simplejson.loads(raw_data)
        begint_ts = post_data.get('begin_ts')
        end_ts = post_data.get('end_ts')
        channel_id = post_data.get('channel_id')
        media_type = post_data.get('type')
        print begint_ts, end_ts, channel_id, media_type


if __name__ == '__main__':
    app = web.application(urls, globals())
    app.run()
