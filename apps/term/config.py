e = Executable("term")

e.require("galaxy_std")
e.require("galaxy_log")
e.require("galaxy_console")
e.require("nebula_core")
e.require("nebula_python","dynamic")
e.require("physx")
e.require("boost_system")
e.require("boost_serialization")
e.require("boost_python")
e.require("boost_thread")
e.require("python27")
#e.require("glfw")

e.make()



