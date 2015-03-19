#!/bin/bash
gnome-terminal -e '../test/server_maze.bash 0'
sleep 1
../test/client_gui.bash 1
