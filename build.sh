#!/bin/bash

#flags='VERBOSE=1'
flags=''

cmake -Hexternal/Galaxy/components/console -Bexternal/Galaxy/components/console/build/Shared/Debug
make -j4 -C external/Galaxy/components/console/build/Shared/Debug --no-print-directory $flags
if [ $? -ne 0 ]; then
	exit 1
fi

cmake -Hcomponents/core -Bcomponents/core/build/Shared/Debug
make -j4 -C components/core/build/Shared/Debug --no-print-directory $flags
if [ $? -ne 0 ]; then
	exit 1
fi

cmake -Hcomponents/gfx -Bcomponents/gfx/build/Shared/Debug
make -j4 -C components/gfx/build/Shared/Debug --no-print-directory $flags
if [ $? -ne 0 ]; then
	exit 1
fi

cmake -Hcomponents/physx -Bcomponents/physx/build/Shared/Debug
make -j4 -C components/physx/build/Shared/Debug --no-print-directory $flags
if [ $? -ne 0 ]; then
	exit 1
fi

cmake -Hcomponents/python -Bcomponents/python/build/Shared/Debug
make -j4 -C components/python/build/Shared/Debug --no-print-directory install $flags
if [ $? -ne 0 ]; then
	exit 1
fi

cmake -Hcomponents/final -Bcomponents/final/build/Shared/Debug
make -j4 -C components/final/build/Shared/Debug --no-print-directory $flags
if [ $? -ne 0 ]; then
	exit 1
fi

cmake -Hcomponents/ext -Bcomponents/ext/build/Shared/Debug
make -j4 -C components/ext/build/Shared/Debug --no-print-directory $flags
if [ $? -ne 0 ]; then
	exit 1
fi

cmake -Happs/box -Bapps/box/build/Shared/Debug
make -j4 -C apps/box/build/Shared/Debug --no-print-directory $flags
if [ $? -ne 0 ]; then
	exit 1
fi

