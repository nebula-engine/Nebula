
dirs = external/maze external/Galaxy/components/log external/Galaxy/components/console components/core components/gfx components/physx components/python components/final components/ext apps/box

all:
	@$(MAKE) -C external/Galaxy/components/std/build/Shared/Debug --no-print-directory
	@$(MAKE) -C external/Galaxy/components/log/build/Shared/Debug --no-print-directory
	@$(MAKE) -C external/Galaxy/components/console/build/Shared/Debug --no-print-directory
	@$(MAKE) -C external/maze/build/Shared/Debug --no-print-directory
	@$(MAKE) -C components/core/build/Shared/Debug --no-print-directory
	@$(MAKE) -C components/gfx/build/Shared/Debug --no-print-directory
	@$(MAKE) -C components/physx/build/Shared/Debug --no-print-directory
	@$(MAKE) -C components/python/build/Shared/Debug --no-print-directory
	@$(MAKE) -C components/final/build/Shared/Debug --no-print-directory
	@$(MAKE) -C components/ext/build/Shared/Debug --no-print-directory
	@$(MAKE) -C apps/box/build/Shared/Debug --no-print-directory
	
cmake:
	@cmake -Hexternal/Galaxy/components/std -Bexternal/Galaxy/components/std/build/Shared/Debug
	@cmake -Hexternal/Galaxy/components/log -Bexternal/Galaxy/components/log/build/Shared/Debug
	@cmake -Hexternal/Galaxy/components/console -Bexternal/Galaxy/components/console/build/Shared/Debug
	@cmake -Hexternal/maze -Bexternal/maze/build/Shared/Debug
	@cmake -Hcomponents/core -Bcomponents/core/build/Shared/Debug
	@cmake -Hcomponents/gfx -Bcomponents/gfx/build/Shared/Debug
	@cmake -Hcomponents/physx -Bcomponents/physx/build/Shared/Debug
	@cmake -Hcomponents/python -Bcomponents/python/build/Shared/Debug
	@cmake -Hcomponents/final -Bcomponents/final/build/Shared/Debug
	@cmake -Hcomponents/ext -Bcomponents/ext/build/Shared/Debug
	@cmake -Happs/box -Bapps/box/build/Shared/Debug

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



