#!/usr/bin/env python
import os
import sys

from celery import Celery
from celery.utils.log import get_task_logger

logger = get_task_logger(__name__)

backend = 'redis://127.0.0.1:6379/0'
broker = 'redis://127.0.0.1:6379/1'

app = Celery('taks', broker = broker, backend = backend)
app.conf.CELERY_RESULT_BACKEND = os.environ.get('CELERY_RESULT_BACKEND', 'redis')
old_outs = sys.stdout, sys.stderr
revel = app.conf.CELERY_REDIRECT_STDOUTS_LEVEL
app.log.redirect_stdouts_to_logger(logger, revel)

@app.task(name='sum_of_two_numbe')
def add( x, y):
    logger.info('Adding {0} + {1}'.format(x,y))
    return x + y

@app.task(name = 'test_name')
def test(username):
    return username

