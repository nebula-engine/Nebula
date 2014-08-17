#!/bin/bash

cmake -Hcomponents/core -Bcomponents/core/build/Shared/Debug
make -j4 -C components/core/build/Shared/Debug

cmake -Hcomponents/gfx -Bcomponents/core/build/Shared/Debug
make -j4 -C components/gfx/build/Shared/Debug

cmake -Hcomponents/physx -Bcomponents/physx/build/Shared/Debug
make -j4 -C components/physx/build/Shared/Debug

cmake -Hcomponents/python -Bcomponents/python/build/Shared/Debug
make -j4 -C components/python/build/Shared/Debug

cmake -Hcomponents/final -Bcomponents/final/build/Shared/Debug
make -j4 -C components/final/build/Shared/Debug

cmake -Hcomponents/ext -Bcomponents/ext/build/Shared/Debug
make -j4 -C components/ext/build/Shared/Debug


