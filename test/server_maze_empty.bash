#!/bin/bash

cmd="./empty --physics --network --python ../share/media/scripts/server_maze_empty.py"

echo $1

if [ $1 -eq "0" ]
then
	$cmd
fi
if [ $1 -eq "1" ]
then
	gdb --args $cmd
fi
if [ $1 -eq "2" ]
then
	valgrind --suppressions=/home/chuck/.valgrind.supp --gen-suppressions=yes $cmd
fi

