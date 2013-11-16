here      := $(shell pwd)
rootname  := C++/
root      := $(shell expr $(here) : '\(.*$(rootname)\)')

mode := lib
os   := lin64

hpaths    := 
hpaths    += $(root)SIG/inc
hpaths    += $(root)external/PhysX/Include
hpaths    += $(root)external
hpaths    += $(root)GRU/inc
hpaths    += $(root)external
hpaths    += $(root)JSL/inc

#lpaths    := 
#lpaths    += $(root)jess/lib/lin64/
#lpaths    += $(root)external/glew/lib
#lpaths    += $(root)external/PhysX/Lib/linux64

defines   := 
defines   += _DEBUG

#libraries := 
#libraries += jess
#libraries += pthread
#libraries += rt
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

-include $(root)../make/Makefile.Cpp.mk
