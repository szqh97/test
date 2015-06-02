#!/bin/bash
set -x
echo "deb http://http.debian.net/debian wheezy-backports main" >>/etc/apt/sources.list
apt-get update
apt-get install -y -t wheezy-backports linux-image-amd64
reboot


