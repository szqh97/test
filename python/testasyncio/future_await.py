#!/usr/bin/env python
# -*- coding: utf-8 -*-
import asyncio

def mark_done(future, result):
    print ('seting future to {!r}'.format(result))
    future.set_result(result)

async def main(loop):
    all_done = asyncio.Future()
    print('secheduling mark_done')
    event_loop.call_soon(mark_done, all_done, 'the result')


    result = await all_done
    print ('future result: {!r}'.format(result))


event_loop = asyncio.get_event_loop()
try:
    event_loop.run_until_complete(main(event_loop))

finally:
    event_loop.close()

