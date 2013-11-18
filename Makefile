here      := $(shell pwd)
rootname  := C++/
root      := $(shell expr $(here) : '\(.*$(rootname)\)')

mode := lib
os   := lin64

hpaths    := 
hpaths    += $(root)kernel/inc
hpaths    += $(root)external/PhysX/Include
hpaths    += $(root)external/glew/include
hpaths    += $(root)Maths/inc
hpaths    += $(root)jess/inc
hpaths    += /afs/unc/proj/walk/include



lpaths    := 
lpaths    += /afs/unc/proj/walk/lib/sgi_irix
lpaths    += $(root)external/PhysX/Lib/linux64



defines   := 
defines   += __DEBUG__
defines   += __LIN__
defines   += __OPENGL__



libraries += rt
libraries += glut
libraries += GLU
libraries += GL
libraries += Xmu
libraries += Xext
libraries += X11
libraries += m
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


-include $(root)../make/Makefile.Cpp.mk


