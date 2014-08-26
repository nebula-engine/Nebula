
dirs = external/maze external/Galaxy/components/log external/Galaxy/components/console components/core components/gfx components/physx components/python components/final components/ext apps/box

all: box

log:
	@$(MAKE) -C external/Galaxy/components/log/build/Shared/Debug --no-print-directory

console:
	@$(MAKE) -C external/Galaxy/components/console/build/Shared/Debug --no-print-directory

maze:
	@$(MAKE) -C external/maze/build/Shared/Debug --no-print-directory


core: console log
	@$(MAKE) -C components/core/build/Shared/Debug --no-print-directory

gfx: core
	@$(MAKE) -C components/gfx/build/Shared/Debug --no-print-directory

physx: core
	@$(MAKE) -C components/physx/build/Shared/Debug --no-print-directory

python: core
	@$(MAKE) -C components/python/build/Shared/Debug --no-print-directory

final: python physx gfx
	@$(MAKE) -C components/final/build/Shared/Debug --no-print-directory

ext: final maze
	@$(MAKE) -C components/ext/build/Shared/Debug --no-print-directory

box: ext
	@$(MAKE) -C apps/box/build/Shared/Debug --no-print-directory
	
cmake:
	@$(foreach dir, $(dirs), cmake -H$(dir) -B$(dir)/build/Shared/Debug;)

clean:
	@$(foreach dir, $(dirs), rm -rf $(dir)/build;)

#
#make -j4 -C components/core/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/gfx/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/physx/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/python/build/Shared/Debug --no-print-directory install $flags
#make -j4 -C components/final/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/ext/build/Shared/Debug --no-print-directory $flags
#make -j4 -C apps/box/build/Shared/Debug --no-print-directory $flags



