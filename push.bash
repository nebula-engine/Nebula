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
}

process "git/nebula-engine/nebula/components/core" master
process "git/nebula-engine/nebula/components/final" master
process "git/nebula-engine/nebula/components/python" master
process "git/nebula-engine/nebula/components/net" master

process "git/nebula-engine/nebula/plugin/gfx1" master
process "git/nebula-engine/nebula/plugin/phx1" master

process "git/nebula-engine/nebula/mod" master

process "git/nebula-engine/nebula/external/cmake" master
process "git/nebula-engine/nebula/external/cmake_find" master

process "git/nebula-engine/nebula/external/Galaxy/components/console" master
process "git/nebula-engine/nebula/external/Galaxy/components/std" master
process "git/nebula-engine/nebula/external/Galaxy/components/log" master
process "git/nebula-engine/nebula/external/Galaxy/components/net" master
process "git/nebula-engine/nebula/external/Galaxy" master
process "git/nebula-engine/nebula/external/maze" master

process "git/nebula-engine/nebula" test


