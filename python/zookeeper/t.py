#!/usr/bin/env python
import os
import logging
import sys
log = logging.getLogger('test-log')
formatter = logging.Formatter('%(threadName)s %(asctime)s %(name)-15s %(levelname)-8s: %(message)s\n')
file_handler = logging.FileHandler('test.log')
file_handler.setFormatter(formatter)
stream_handler = logging.StreamHandler(sys.stderr)
log.addHandler(file_handler)
log.addHandler(stream_handler)

log.info('sss')


