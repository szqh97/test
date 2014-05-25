#!/bin/sh
taskf100="task_ts100.`date +%m%d%H`"
grep ts100 /opt/rtfp/var/log/taskgenerator.log|tail -n 1 |sed 's/^.*data is://g' >$taskf
newtaskf100="newtask_ts100.`date +%m%d%H` "
python gen_nestream_publish_msg.py $task100 $newtaskf100

taskf200="task_ts200.`date +%m%d%H`"
grep ts200 /opt/rtfp/var/log/taskgenerator.log|tail -n 1 |sed 's/^.*data is://g' >$taskf
newtaskf200="newtask_ts200.`date +%m%d%H` "
python gen_nestream_publish_msg.py $task200 $newtaskf200
