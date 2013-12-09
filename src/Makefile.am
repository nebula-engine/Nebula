lib_LIBRARIES = libneb.a

libneb_a_SOURCES = \
		neb/physics.h neb/physics.cpp \
		neb/scene.h neb/scene.cpp \
		neb/view.h neb/view.cpp \
		neb/actor/Base.h neb/actor/Base.cpp \
		neb/actor/actor.h neb/actor/Actor.cpp \
		neb/actor/Rigid_Actor.h neb/actor/Rigid_Actor.cpp \
		neb/actor/Rigid_Body.h neb/actor/Rigid_Body.cpp \
		neb/actor/Rigid_Dynamic.h neb/actor/Rigid_Dynamic.cpp \
		neb/actor/Rigid_Static.h neb/actor/Rigid_Static.cpp \
		neb/actor/Light.h neb/actor/Light.cpp \
		neb/actor/Controller.h neb/actor/Controller.cpp


nobase_include_HEADERS = \
		neb/physics.h \
		neb/scene.h \
		neb/view.h \
		neb/actor/Base.h \
		neb/actor/Actor.h \
		neb/actor/Rigid_Actor.h \
		neb/actor/Rigid_Body.h \
		neb/actor/Rigid_Dynamic.h \
		neb/actor/Rigid_Static.h \
		neb/actor/Light.h \
		neb/actor/Controller.h

CXXFLAGS = -std=c++0x -DNEB_PREFIX=${includedir} -D_DEBUG

