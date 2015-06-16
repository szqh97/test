#!/usr/bin/env python
import logging

logger = logging
def install_logger():
    global logger
    logger = logging.getLogger('myapp')
    hdlr = logging.FileHandler('/dev/stdout')
    formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
    hdlr.setFormatter(formatter)
    logger.addHandler(hdlr)
    logger.setLevel(logging.DEBUG)

if __name__ == '__main__':
    install_logger()
    logger.info("while a test")
    logger.error("teststst")
