#!/usr/bin/env python
"""
USAGE: rename this file to .pythonstartup
set PYTHONSTARTUP
export PYTHONSTARTUP=~/.pythonstartup
"""
import readline
import rlcompleter
import atexit
import os
#tab completion
readline.parse_and_bind('tab: complete')
# history file
histfile = os.path.join(os.environ['HOME'], '.pythonhistory')
try:
    readline.read_history_file(hisfile)
except IOError:
    pass
atexit.register(readline.write_history_file, histfile)
del os, histfile, readline, rlcompleter
