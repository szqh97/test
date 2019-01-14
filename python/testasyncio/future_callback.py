#!/usr/bin/env python
# -*- coding: utf-8 -*-
import asyncio
import functools

def callback(future, n):
    print ('{}: future done: {}'.format(n, future.result()))


async def register_callback(all_done):
    print ("registering callback on future")
    all_done.add_done_callback(functools.partial(callback, n = 1))
    all_done.add_done_callback(functools.partial(callback, n = 2))

async def main(all_done):
    await register_callback(all_done)
    all_done.set_result('jj')

event_loop = asyncio.get_event_loop()
try:
    future = asyncio.Future()
    event_loop.run_until_complete(main(future))

finally:
    event_loop.close()

