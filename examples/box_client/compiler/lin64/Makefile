here      := $(shell pwd)
rootname  := cpp_projects/
root      := $(shell expr $(here) : '\(.*$(rootname)\)')



hpaths    :=
hpaths    += $(root)jess/inc
hpaths    += $(root)nebula/inc
hpaths    += $(root)external/glew/include
hpaths    += $(root)external/PhysX/Include

lpaths    :=
lpaths    += $(root)jess/lib/lin64
lpaths    += $(root)nebula/lib/lin64
lpaths    += $(root)external/glew/lib
lpaths    += $(root)external/PhysX/Lib/linux64

defines   := 
defines   += FLOAT=float
defines   += __DEBUG__
defines   += __LIN__
defines   += __OPENGL__

libraries :=
libraries += jess
libraries += nebula
libraries += boost_system
libraries += pthread
libraries += rt
libraries += PhysX3
libraries += SimulationController
libraries += LowLevel
libraries += LowLevelCloth
libraries += PhysXProfileSDK
libraries += PhysX3Extensions
libraries += SceneQuery
libraries += PhysX3Common
libraries += PhysX3CharacterKinematic
libraries += PhysX3Vehicle
libraries += PhysX3Cooking
libraries += PvdRuntime
libraries += RepX3
libraries += PxTask
libraries += X11
libraries += GL
libraries += GLU
libraries += GLEW



-include $(root)make/Makefile.Bin.mk
