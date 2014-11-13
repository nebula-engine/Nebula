#ifndef NEB_PY_CORE_POSE_HPP
#define NEB_PY_CORE_POSE_HPP

#include <boost/python.hpp>

#include <neb/core/pose.hpp>

namespace bp = boost::python;

void	export_pose();

namespace neb {
	namespace py {
		namespace core {
			class pose: public neb::core::pose {
				public:
					bp::list	getPos() {
						bp::list l;
						l.append(pos_[0]);
						l.append(pos_[1]);
						l.append(pos_[2]);
						l.append(pos_[3]);
						return l;
					}
			};
		}
	}
}

/*BOOST_PYTHON_MODULE(libneb-py) {

  class_<neb::core::pose>("pose")
  .def("p", &neb::core::pose::pos_)
  .def("q", &neb::core::pose::rot_)
  ;

  }*/

#endif

