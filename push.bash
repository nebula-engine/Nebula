#!/bin/bash

function git_dirty {
	expr $(git status --porcelain 2>/dev/null| egrep "^(M| M)" | wc -l)
}

function git_untracked {
	expr $(git status --porcelain 2>/dev/null| grep "^??" | wc -l)
}

process () {
	cd
	cd $1

	#echo $1
	echo "cargs = $#"

	if [ $# -eq 3 ]
	then

		if [[ (`git_dirty` != 0) || (`git_untracked` != 0) ]]; then
			git add --all
			git commit -m "$3"
			git push origin $2
		fi
	else
		if [[ (`git_dirty` != 0) || (`git_untracked` != 0) ]]; then
			echo dirty
			git add --all
			git commit < /dev/tty
			git push origin $2
		fi
	fi
}

while read loc remote
do
	if [ $# -eq 1 ]
	then
       		process $loc $remote "$1"
	else
	       	process $loc $remote
	fi
done < "repo_list.txt"


