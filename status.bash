#!/bin/bash


process () {
	cd
	cd $1

	echo $1

	git status
}

process "git/nebula-engine/nebula/components/core" master
process "git/nebula-engine/nebula/components/python" master

process "git/nebula-engine/nebula/plugin/gfx1" master
process "git/nebula-engine/nebula/plugin/phx1" master
process "git/nebula-engine/nebula/plugin/net1" master

process "git/nebula-engine/nebula/mod" master

process "git/nebula-engine/nebula/external/cmake" master
process "git/nebula-engine/nebula/external/cmake_find" master

process "git/nebula-engine/nebula/external/Galaxy/components/console" master
process "git/nebula-engine/nebula/external/Galaxy/components/std" master
process "git/nebula-engine/nebula/external/Galaxy/components/log" master
process "git/nebula-engine/nebula/external/Galaxy/components/net" master
process "git/nebula-engine/nebula/external/Galaxy" master
process "git/nebula-engine/nebula/external/maze" master

process "git/nebula-engine/nebula" neb67


