#!/bin/bash
kill $(ps aux | grep '../test/server' | awk '{print $2}')
sleep 1
../test/server_maze_empty.bash 0 > log 2>&1 &
sleep 1
../test/client.bash 0

