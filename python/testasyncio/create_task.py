#!/usr/bin/env python
# -*- coding: utf-8 -*-
import asyncio
async def task_func():
    print ("in task func")
    return 'the result'

async def main(loop):
    print ('creating task')
    task = loop.create_task(task_func())
    print ()
