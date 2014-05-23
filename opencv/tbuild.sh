#!/bin/sh
set -x
g++ -ggdb `pkg-config --cflags tesseract` $@ `pkg-config --libs tesseract`
