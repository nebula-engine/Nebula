here      := $(shell pwd)
rootname  := cpp_projects/
root      := $(shell expr $(here) : '\(.*$(rootname)\)')



hpaths    := 
hpaths    += $(root)external/PhysX-3.2.4_LINUX_SDK_Core/Include
hpaths    += $(root)external/glew/include
hpaths    += $(root)jess/inc

lpaths    := 
lpaths    += $(root)jess/lib/lin64/
lpaths    += $(root)external/glew/lib
lpaths    += $(root)external/PhysX-3.2.4_LINUX_SDK_Core/Lib/linux64

defines   := 
defines   += FLOAT=float
defines   += __DEBUG
defines   += __LINUX
defines   += __OPENGL
defines   += _DEBUG

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
