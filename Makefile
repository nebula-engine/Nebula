
dirs = external/Galaxy/components/console components/core components/gfx components/physx

all:
	./build.sh

cmake:
	@$(foreach dir, $(dirs), cmake -H$(dir) -B$(dir)/build/Shared/Debug

all:

clean:
	@$(foreach dir, $(dirs), rm -rf $(dir)/build;)

#make -j4 -C external/Galaxy/components/console/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/core/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/gfx/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/physx/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/python/build/Shared/Debug --no-print-directory install $flags
#make -j4 -C components/final/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/ext/build/Shared/Debug --no-print-directory $flags
#make -j4 -C apps/box/build/Shared/Debug --no-print-directory $flags



