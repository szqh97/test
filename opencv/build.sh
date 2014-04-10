#!/bin/sh
set -x
g++ -ggdb `pkg-config --cflags opencv` $@ `pkg-config --libs opencv`
