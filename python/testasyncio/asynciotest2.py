#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import asyncio

@asyncio.coroutine
def my_coroutine(task_name, second_to_sleep = 3):
    print("{} sleeping for {} second".format(task_name, second_to_sleep))
    yield from asyncio.sleep(second_to_sleep)
    print("{} is finished".format(task_name))

loop = asyncio.get_event_loop()

tasks = [
        my_coroutine("task1", 3),
        my_coroutine("task2", 9),
        my_coroutine("task3", 5),
        my_coroutine("task4", 2),
        my_coroutine("task5", 1)
        ]
loop.run_until_complete(
        asyncio.wait(tasks)
    )
loop.close()

