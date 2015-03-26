#!/bin/bash

#../test/test.bash $1 './test_no_gui --network --physics'

#../test/server_maze_empty.bash $1

../test/kill.bash

echo server

../test/server_no_gui.bash 0 > log 2>&1 &
sleep 3


