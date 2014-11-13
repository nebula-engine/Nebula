
#include <boost/python.hpp>

#include <neb/py/core/pose.hpp>

void		export_pose() {

	boost::python::class_<neb::py::core::pose>("pose")
		.def("getPos", &neb::py::core::pose::getPos);
//		.def_readwrite("q", &neb::core::pose::rot_)
//		;

}





