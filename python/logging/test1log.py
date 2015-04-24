#!/usr/bin/env python
import logging
import sys
log = logging.getLogger('test-log')
formatter = logging.Formatter('%(threadName)s %(asctime)s %(name)-15s %(levelname)-8s: %(message)s')
file_handler = logging.FileHandler('./test1log.log')
file_handler.setFormatter(formatter)
stream_handler = logging.StreamHandler(sys.stderr)
stream_handler.setFormatter(formatter)
log.addHandler(file_handler)
log.addHandler(stream_handler)

log.info('test info')
log.error('test error')
