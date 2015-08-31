#!/bin/bash
#set -x
exec_file=$(echo $1|cut -d"." -f1)
rustc $1 && ./$exec_file
rm $exec_file

