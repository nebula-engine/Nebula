#!/bin/bash

#../test/test.bash $1 './test_no_gui --network --physics'

#../test/server_maze_empty.bash $1
ps aux | grep "../test/server" | awk "{print $2}"
../test/server_no_gui.bash 0 > log 2>&1 &

