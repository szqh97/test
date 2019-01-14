#!/usr/bin/env python
# -*- coding: utf-8 -*-
import asyncio
import time

def callback(n, loop):
    print('callback {} invoked at {}'.format(n, loop.time()))

async def main(loop):
    now = loop.time()
    print('clock time: {}'.format(time.time()))
    print('loop  time: {}'.format(now))


    print('registering')
    loop.call_at(now + 1, callback, 1, loop)
    loop.call_at(now + 2, callback, 2, loop)
    loop.call_soon(callback, 3, loop)

    await asyncio.sleep(4)


event_loop = asyncio.get_event_loop()
try:
    print ('entering')
    event_loop.run_until_complete(main(event_loop))
finally:
    event_loop.close()

