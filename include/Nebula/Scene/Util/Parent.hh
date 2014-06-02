#ifndef NEBULA_SCENE_UTIL_PARENT_HH
#define NEBULA_SCENE_UTIL_PARENT_HH

#include <Galaxy-Standard/map.hpp>
#include <Galaxy-Standard/parent.hpp>

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

