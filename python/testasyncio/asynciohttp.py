#!/usr/bin/env python
# -*- coding: utf-8 -*-
import asyncio
import aiohttp

@asyncio.coroutine
def fetch_page(url, pause=False):
    if pause:
        yield from asyncio.sleep(2)
    response = yield from aiohttp.request("GET", url)
    assert response.status == 200
    content = yield from response.read()
    print ("URL: {}: content: {}".format(url, content[0:10]))

loop = asyncio.get_event_loop()
tasks = [
        fetch_page("http://www.baidu.com"),
        fetch_page("http://www.renren.com"),
        fetch_page("http://www.renren.com", True)
        ]
loop.run_until_complete(asyncio.wait(tasks))
loop.close()

for task in tasks:
    print(task)

