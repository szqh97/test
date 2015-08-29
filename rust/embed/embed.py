#!/usr/bin/env python
# -*- coding: utf-8 -*-
from ctypes import cdll
lib = cdll.LoadLibrary('./target/release/libembed.so')
lib.process()
print ("Done")
