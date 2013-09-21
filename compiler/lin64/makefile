root      := /home/charles/cpp_projects/

hpaths    := 
hpaths    += $(root)external/PhysX-3.2.4_LINUX_SDK_Core/Include
hpaths    += $(root)external/glew/include
hpaths    += $(root)transfer/jess/inc

lpaths    := 
lpaths    += $(root)transfer/jess/lib/lin64/
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

-include $(root)transfer/make/makefile.Lib.mk
