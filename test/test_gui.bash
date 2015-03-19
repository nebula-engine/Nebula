#!/bin/bash
gnome-terminal --full-screen -e "../test/server_maze.bash $1"
sleep 2
../test/client_gui.bash $1
