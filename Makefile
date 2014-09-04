
build_dir = build/Shared/Debug

all:
	@$(MAKE) -C $(build_dir) --no-print-directory
cmake:
	@cmake -H -B$(build_dir)

clean:
	@$(MAKE) clean -C $(build_dir) --no-print-directory

#
#make -j4 -C components/core/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/gfx/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/physx/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/python/build/Shared/Debug --no-print-directory install $flags
#make -j4 -C components/final/build/Shared/Debug --no-print-directory $flags
#make -j4 -C components/ext/build/Shared/Debug --no-print-directory $flags
#make -j4 -C apps/box/build/Shared/Debug --no-print-directory $flags



