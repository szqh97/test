#!/usr/bin/env bash
g++ hello.cpp -shared -fPIC -o hello_ext.so -I /usr/include/python2.7 -lboost_python
