#!/bin/bash
set -x
cd /vobiledata/
cd /vobiledata/ &&  wget http://192.168.110.34:12345/videotracker-docker-debian7_32bit.tgz
tar xvzf videotracker-docker-debian7_32bit.tgz 
docker load -i videotracker-docker-debian7_32bit.tar
wget http://192.168.110.34:12345/install.tar.gz
tar xvzf install.tar.gz
