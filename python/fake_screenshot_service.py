#!/usr/bin/env python
import re
import os
import sys
import logging
import logging.config
import web
import time
import uuid
import random 
import string
import simplejson
import collections
from web import webapi


urls = ("/fakescreenshot", "fake_screenshot_service")


class fake_screenshot_service:
    def __init__(self):
        self.max_reservetime = 7*24

    def varify_params(self, requestId, begin_ts, end_ts, media_type, channel_uuid):
        if begin_ts >= end_ts:
            err_info = {"requestId":requestId, "error": {"code": 400, "message": "begin_ts is larger or equal to end_ts"}}
            web.debug("error: %s"% str(err_info))
            err_info = simplejson.dumps(err_info)
            raise web.webapi._status_code("400 Bad Request", web.webapi.BadRequest, "begin_ts is larger or equal to end_ts"), err_info
        
        ltime = int(time.time())
        if begin_ts < ltime - self.max_reservetime * 3600:
            err_info = {"requestId":requestId, "error": {"code": 400, "message": "begin_ts is not in reserved time"}}
            web.debug("error: %s"% str(err_info))
            err_info = simplejson.dumps(err_info)
            raise web.webapi._status_code("400 Bad Request", web.webapi.BadRequest, "begin_ts is not in reserved time"), err_info
        
        if media_type.lower() not in ('video', 'screenshot'):
        
            err_info = {"requestId":requestId, "error": {"code": 400, "message": "type is error"}}
            web.debug("error: %s"% str(err_info))
            err_info = simplejson.dumps(err_info)
            raise web.webapi._status_code("400 Bad Request", web.webapi.BadRequest, "type is error"), err_info
        
        if channel_uuid is None:
            web.debug(" channel uuid is null")
            err_info = {"requestId":requestId, "error": {"code": 400, "message": "the channel uuid is not error"}}
            web.debug("error: %s"% str(err_info))
            err_info = simplejson.dumps(err_info)
            raise web.webapi._status_code("400 Bad Request", web.webapi.BadRequest, "the channel uuid is not using"), err_info

    def POST(self):
        raw_data = web.data()
        requestId = str(uuid.uuid4())
        print raw_data
        post_data = simplejson.loads(raw_data)
        begin_ts = post_data.get('beginTimestamp')
        end_ts = post_data.get('endTimestamp')
        channel_uuid = post_data.get('channelUuid')
        media_type = post_data.get('type')
        self.varify_params(requestId, begin_ts, end_ts, media_type, channel_uuid)
        downurl = "http://10.198.159.221/fake_screenshot.tgz"

        response_info = {
                "requestId":requestId,
                "error":None,
                "resultUrl":downurl
                }

        return simplejson.dumps(response_info)

if __name__ == '__main__':
    app = web.application(urls, globals())
    app.run()
