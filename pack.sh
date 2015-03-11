#!/bin/bash

<<<<<<< HEAD
# to be called from build dir

root='../'

=======
>>>>>>> eca49debfb62ef0d3ad2978e4f1ab5e74208aef9
mkdir install_files -p
cd install_files
rm -rf *

mkdir libs -p

<<<<<<< HEAD


cp -r ../share .
cp ../INSTALL .

# libs
#cp ($root)components/core/build/static/libnebula_core.a libs/

cp ($root)components/python/libnebula_python_0_so_db.so libs/

cp ($root)plugin/phx1/build/dynamic/libnebula_physx_0_so_db.so libs/
cp ($root)plugin/gfx1/build/dynamic/libnebula_physx_0_so_db.so libs/
cp ($root)plugin/net1/build/dynamic/libnebula_physx_0_so_db.so libs/

#cp ../build/Shared/Debug/external/Galaxy/components/std/libgalaxy_std_0_so_db.so libs/
#cp ../build/Shared/Debug/external/Galaxy/components/log/libgalaxy_log_0_so_db.so libs/
#cp ../build/Shared/Debug/external/Galaxy/components/console/libgalaxy_console_0_so_db.so libs/

#cp /scratch/usr/lib/libglfw.so.3 libs/
#cp /scratch/usr/lib/libboost_serialization.so.1.55.0 libs/
#cp /scratch/usr/lib/libboost_system.so.1.55.0 libs/
#cp /scratch/usr/lib/libboost_thread.so.1.55.0 libs/
#cp /scratch/usr/lib/libboost_python.so.5 libs/

#cp /scratch/usr/lib64/libstdc++.so.6 libs/
#cp /scratch/usr/lib64/libgcc_s.so.1 libs/
=======
cp -r ../share/* .
cp ../INSTALL .

# libs
cp ../build/Shared/Debug/components/core/libnebula_core_0_so_db.so libs/
cp ../build/Shared/Debug/components/physx/libnebula_physx_0_so_db.so libs/
cp ../build/Shared/Debug/components/final/libnebula_final_0_so_db.so libs/
cp ../build/Shared/Debug/components/python/libnebula_python_0_so_db.so libs/

cp ../build/Shared/Debug/external/Galaxy/components/std/libgalaxy_std_0_so_db.so libs/
cp ../build/Shared/Debug/external/Galaxy/components/log/libgalaxy_log_0_so_db.so libs/
cp ../build/Shared/Debug/external/Galaxy/components/console/libgalaxy_console_0_so_db.so libs/

cp /scratch/usr/lib/libglfw.so.3 libs/
cp /scratch/usr/lib/libboost_serialization.so.1.55.0 libs/
cp /scratch/usr/lib/libboost_system.so.1.55.0 libs/
cp /scratch/usr/lib/libboost_thread.so.1.55.0 libs/
#cp /scratch/usr/lib/libboost_python.so.5 libs/

cp /scratch/usr/lib64/libstdc++.so.6 libs/
cp /scratch/usr/lib64/libgcc_s.so.1 libs/
>>>>>>> eca49debfb62ef0d3ad2978e4f1ab5e74208aef9

# mods
cp ../build/Shared/Debug/components/ext/hf/libnebula_ext_hf_0_so_db.so media/mods/

<<<<<<< HEAD
# apps
=======
>>>>>>> eca49debfb62ef0d3ad2978e4f1ab5e74208aef9
cp ../build/Shared/Debug/apps/hf/hf_0_so_db .



