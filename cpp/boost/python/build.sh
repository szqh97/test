#!/usr/bin/env bash
rm hello_ext.so
g++ hello.cpp -shared -fPIC -o hello_ext.so -I /usr/include/python2.7 -lboost_python
