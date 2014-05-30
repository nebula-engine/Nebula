#ifndef NEBULA_SCENE_UTIL_PARENT_HH
#define NEBULA_SCENE_UTIL_PARENT_HH

#include <Nebula/Util/Map.hh>
#include <Nebula/Util/Parent.hh>

#include <Nebula/Core/Pose.hh>

#include <Nebula/Scene/Util/Types.hh>

namespace Neb {
	namespace Scene {
		namespace Util {
			class Parent:
				virtual public Neb::Util::Parent<Neb::Scene::Base>,
				virtual public Neb::Util::Shared,
				virtual public Neb::Core::Pose
			{
				public:
			};
		}
	}
}

#endif

