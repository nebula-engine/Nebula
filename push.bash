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

	echo $1

	if [ $# -eq 3 ]
	then

		if [ `git_dirty` != 0 ]; then
			echo dirty
			git add --all
			git commit -m "$3"
			git push origin $2
		elif [ `git_untracked` != 0 ]; then 
			echo dirty
			git add --all
			git commit -m "$3"
			git push origin $2
		else
			echo clean
		fi
	
	else
		if [ `git_dirty` != 0 ]; then
			echo dirty
			git add --all
			git commit
			git push origin $2
		elif [ `git_untracked` != 0 ]; then 
			echo dirty
			git add --all
			git commit
			git push origin $2
		else
			echo clean
		fi

	fi
}

echo $1

cm=$1

echo $cm

if [ $# -eq 1 ]
then
	cm="$cm"
	echo $cm
fi

process "git/nebula-engine/nebula/components/fnd0" master $cm
#process "git/nebula-engine/nebula/components/fnd1" master "$1"
process "git/nebula-engine/nebula/components/python" master $cm

process "git/nebula-engine/nebula/plugin/gfx1" master $cm
process "git/nebula-engine/nebula/plugin/phx1" master $cm
process "git/nebula-engine/nebula/plugin/net1" master $cm

process "git/nebula-engine/nebula/mod" master $cm

process "git/nebula-engine/nebula/external/cmake" master $cm
process "git/nebula-engine/nebula/external/cmake_find" master $cm

process "git/nebula-engine/nebula/external/Galaxy/components/console" master $cm
process "git/nebula-engine/nebula/external/Galaxy/components/std" master $cm
process "git/nebula-engine/nebula/external/Galaxy/components/log" master $cm
process "git/nebula-engine/nebula/external/Galaxy/components/net" master $cm
process "git/nebula-engine/nebula/external/Galaxy" master $cm
process "git/nebula-engine/nebula/external/maze" master $cm

process "git/nebula-engine/nebula" neb67 $cm


