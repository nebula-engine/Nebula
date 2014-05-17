#ifndef NEBULA_SCENE_UTIL_PARENT_HH
#define NEBULA_SCENE_UTIL_PARENT_HH

#include <Nebula/Util/Map.hh>

#include <Nebula/Core/Pose.hh>

#include <Nebula/Scene/Util/Types.hh>

namespace Neb {
	namespace Scene {
		namespace Util {
			class Parent: virtual public Neb::Util::Shared, virtual public Neb::Core::Pose {
				public:
					Neb::Scene::Base_s			getScene(int);
					Neb::Scene::Base_s			getScene(Neb::Scene::Util::Address);

					void					insertScene(Neb::Scene::Base_s scene);
					void					insertScene(Neb::Scene::Base_s scene, int i);
				private:
					Neb::Map<Neb::Scene::Base>		scenes_;
			};
		}
	}
}

#endif

