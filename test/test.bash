#!/bin/bash

if [ $1 -eq "0" ]
then
	$2
fi
if [ $1 -eq "1" ]
then
	#gdb -x ../test/run.gdb --args $2
	gdb --args $2
fi
if [ $1 -eq "2" ]
then
	valgrind --suppressions=/home/chuck/.valgrind.supp --gen-suppressions=yes $2
fi

