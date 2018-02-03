#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import asyncio

@asyncio.coroutine
def my_coroutine(future, task_name, second_to_sleep = 3):
    print("{} sleeping for {} second".format(task_name, second_to_sleep))
    yield from asyncio.sleep(second_to_sleep)
    print("{} is finished".format(task_name))

def got_result(future):
    print(future.result())


loop = asyncio.get_event_loop()
future1 = asyncio.Future()
future2 = asyncio.Future()
tasks = [
        my_coroutine(future1, "task1", 3),
        my_coroutine(future2, "task2", 10)
        ]

future1.add_done_callback(got_result)
future2.add_done_callback(got_result)

loop.run_until_complete(asyncio.wait(tasks))
loop.close()

