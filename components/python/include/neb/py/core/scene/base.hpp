#ifndef NEB_PY_CORE_SCENE_BASE
#define NEB_PY_CORE_SCENE_BASE

#include <boost/python.hpp>

#include <neb/core/core/scene/util/decl.hpp>

using namespace std;

void		export_scene();

namespace neb {
	namespace py {
		namespace core {
			namespace scene {

				class base {
					public:
						void					createActorRigidStaticCube(
								boost::python::object& pose, boost::python::object& size);
						weak_ptr<neb::core::core::scene::base>		scene_;
				};
			}
		}
	}
}

#endif
