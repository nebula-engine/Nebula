#!/bin/bash


process () {
	cd
	cd $1

	echo $1

	git status
}


while read loc remote
do
	process $loc $remote
done < "repo_list.txt"



