
#include <boost/python.hpp>

#include <neb/core/pose.hpp>
#include <neb/core/core/scene/base.hpp>

#include <neb/py/core/scene/base.hpp>
#include <neb/py/core/pose.hpp>


void		neb::py::core::scene::base::createActorRigidStaticCube(boost::python::object& pose_obj, boost::python::object& size_obj) {
	
//	auto pose = boost::python::extract<neb::core::pose&>(pose_obj);
	neb::core::pose pose;

	double size = bp::extract<double>(size_obj);
	
	auto scene(scene_.lock());
	assert(scene);

	scene->createActorRigidStaticCube(pose, size);
	
}

void		export_scene() {

	boost::python::class_<neb::py::core::scene::base>("scene")
		.def("createActorRigidStaticCube", &neb::py::core::scene::base::createActorRigidStaticCube);
	//        .def("greet", &World::greet)
	//       .def("set", &World::set)
	//    ;
}






