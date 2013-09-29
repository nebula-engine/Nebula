#!/bin/bash -e


perl -pe "s/$2/$3/g" $1 > $1.temp

if [ $? -ne 0 ]; then
	exit
fi


rm $1
mv $1.temp $1

echo "modified $1"

