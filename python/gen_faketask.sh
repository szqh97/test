#!/bin/sh
./fake_taskgen.py channels.pkl task  >faketask_`date +%Y%m%d_%H%M%S`.log 2>&1
