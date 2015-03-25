#!/bin/bash

#../test/test.bash $1 './test_no_gui --network --physics'

#../test/server_maze_empty.bash $1

echo start

ps aux | grep "./test_server_no_gui"
ps aux | grep "../test/server_no_gui"

echo cleanup start

kill $(ps aux | grep "./test_server_no_gui" | awk '{print $2}')
kill $(ps aux | grep "../test/server_no_gui" | awk '{print $2}')

echo cleanup finish

ps aux | grep "./test_server_no_gui"
ps aux | grep "../test/server_no_gui"

echo server

../test/server_no_gui.bash 0 > log 2>&1 &

