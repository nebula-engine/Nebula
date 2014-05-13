#ifndef NEBULA_SCENE_UTIL_PARENT_HH
#define NEBULA_SCENE_UTIL_PARENT_HH

#include <Nebula/Util/Map.hpp>

namespace Neb {
	namespace Scene {
		namespace Util {
			class Parent: virtual public Neb::Shared, virtual public Neb::Core::Pose {
				public:
					
					
				private:
					Neb::Map<Neb::Scene::Scene>		scenes_;
			};
		}
	}
}

#endif

