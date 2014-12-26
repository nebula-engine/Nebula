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
		git push origin master
	elif [ `git_untracked` != 0 ]; then 
		echo dirty
		git add --all
		git commit 
		git push origin master
	else
		echo clean
	fi
}

process "git/nebula-engine/nebula/components/core"
process "git/nebula-engine/nebula/components/gfx"
process "git/nebula-engine/nebula/components/physx"
process "git/nebula-engine/nebula/components/final"
process "git/nebula-engine/nebula/components/python"
process "git/nebula-engine/nebula/components/ext"

process "git/nebula-engine/nebula/external/cmake"
process "git/nebula-engine/nebula/external/cmake_find"

process "git/nebula-engine/nebula/external/Galaxy/components/console"
process "git/nebula-engine/nebula/external/Galaxy/components/std"
process "git/nebula-engine/nebula/external/Galaxy/components/log"
process "git/nebula-engine/nebula/external/Galaxy"

