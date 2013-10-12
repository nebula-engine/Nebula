here      := $(shell pwd)
rootname  := cpp_projects/
root      := $(shell expr $(here) : '\(.*$(rootname)\)')



hpaths    := 
hpaths    += $(root)external/boost_1_54_0
hpaths    += $(root)external/PhysX/Include
hpaths    += $(root)external/glew/include
hpaths    += $(root)external
hpaths    += $(root)jess/inc

lpaths    := 
lpaths    += $(root)jess/lib/lin64/
lpaths    += $(root)external/glew/lib
lpaths    += $(root)external/PhysX/Lib/linux64

defines   := 
defines   += __DEBUG__
defines   += __LIN__
defines   += __OPENGL__

libraries := 
libraries += jess
libraries += pthread
libraries += rt
libraries += PhysX3
libraries += SimulationController
libraries += LowLevel
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

-include $(root)make/Makefile.Lib.mk
