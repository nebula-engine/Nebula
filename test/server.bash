#!/bin/bash

cmd="./empty --network --python ../share/media/scripts/basic_server.py"

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

