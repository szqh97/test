#!/usr/bin/env python
# -*- coding: utf-8 -*-
import asyncio

async def coroutine():
    print ('in coroutine')
    return 'result'

event_loop = asyncio.get_event_loop()

try:
    print ('starting coroutine')
    coro = coroutine()
    print ('entering event loop')
    ret = event_loop.run_until_complete(coro)
    print(ret)

finally:
    event_loop.close()
