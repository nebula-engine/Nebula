#!/bin/bash -e


perl -pe "s/$1/$2/g" $3 > $3.temp

if [ $? -ne 0 ]; then
	exit
fi


rm $3
mv $3.temp $3

echo "modified $3"

