#!/usr/bin/env python
import os
import logging
import sys
import traceback
import optparse
from optparse import OptionParser
log = logging.getLogger('zk-utils')
formatter = logging.Formatter('%(threadName)s %(asctime)s %(name)-15s %(levelname)-8s: %(message)s\n')
file_handler = logging.FileHandler('/tmp/zk-utils.log')
file_handler.setFormatter(formatter)
stdout_stream = logging.StreamHandler(sys.stdout)
log.addHandler(file_handler)
log.addHandler(stdout_stream)
log.setLevel(logging.DEBUG)

sys.path.append(os.path.normpath(os.path.join(sys.path[0],os.path.realpath(__file__))))
from kazoo import client

ROOT_ZNODE = '/config/crawler'

class sync_crawler_config(client.KazooClient):
    def __init__(self, hosts, config_file, znode = None, force_update=False):
        self.hosts = hosts
        self.config_file = config_file
        self.znode = znode
        self.force_update = force_update
        self.do_init()

    def do_start(self):
        self.zk_instance.start()

    def do_init(self):
        if not self.znode:
            _znode = self.config_file.split(os.sep)[-1]
            self.znode = os.path.normpath(os.path.join(ROOT_ZNODE, _znode))
        try:
            self.zk_instance = client.KazooClient(self.hosts)
            self.do_start()
        except Exception, e:
            log.error('create zk instance error: %s', traceback.format_exc())

        if not self.zk_instance.connected:
            log.error('start zookeeper client error!')


    def update_configfile(self):
        if not os.path.exists(self.config_file):
            log.error('config file: %s not exist!', self.config_file)
            return 
        try:
            value_data = file(self.config_file, 'r').read()
            if not self.zk_instance.exists(self.znode):
                self.zk_instance.create(self.znode, value_data, makepath=True)
            else:
                self.zk_instance.ensure_path(self.znode)
                if self.force_update:
                    self.zk_instance.set(self.znode, value_data)
                else:
                    log.info('config file has already exist, use -f to replace it')
                    return
        except Exception, e:
            log.error('create node %s error: %s', self.znode, traceback.format_exc())
            return
        finally:
            self.zk_instance.stop()
        log.info('update config file sucess')
        return True

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('-s', '--server', dest = 'server', type = 'string', metavar = 'string',
            help = 'zookeeper hosts')
    parser.add_option('-f', '--force', dest = 'force_update', default = False, action = 'store_true',
            help = 'force update config file')
    parser.add_option('-c', '--config-file', dest= 'config_file', metavar = 'string',
            help = 'config file name')
    parser.add_option('-n', '--node', dest = 'znode', metavar = 'string', default = None,
            help = 'node name in zookeeper')
    option, args = parser.parse_args()

    if option.server and option.config_file:
        server = option.server
        config_file = option.config_file
        force_update = option.force_update
        node = option.znode
        zk_client = sync_crawler_config(server, config_file, node, force_update)
        log.info("server is: %s, config_file is: %s, force_update is %s, node is %s", server, config_file, force_update, node)
        zk_client.update_configfile()
    else:
        parser.set_usage('zk_utils.py -s 127.0.0.1:2181 -c crawler.conf [-f -n crawler]')
        print parser.print_help()

