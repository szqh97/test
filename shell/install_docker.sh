#!/bin/bash
set -x

apt-get install -y curl
curl -sSL https://get.docker.com/ | sh

cat >>/etc/default/docker <<EOF
DOCKER_OPTS="
    -H unix:///var/run/docker.sock 
    -H tcp://0.0.0.0:2375 
    --graph /vobiledata/docker/lib/docker
    --mtu 1462
"
EOF
/etc/init.d/docker restart
curl -L https://github.com/docker/compose/releases/download/1.2.0/docker-compose-`uname -s`-`uname -m` > /usr/local/bin/docker-compose
chmod +x /usr/local/bin/docker-compose

