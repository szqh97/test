#!/usr/bin/env python
# -*- coding: utf-8 -*-
import asyncio

def mark_done(future, result):
    print ('seting future to {!r}'.format(result))
    future.set_result(result)


event_loop = asyncio.get_event_loop()
try:
    all_done = asyncio.Future()

    print('secheduling mark_done')
    event_loop.call_soon(mark_done, all_done, 'the result')

    print("entering eventloop")
    result = event_loop.run_until_complete(all_done)

    print ('resulting result: {!r}'.format(result))
finally:
    event_loop.close()

print ('future result: {!r}'.format(all_done.result()))
