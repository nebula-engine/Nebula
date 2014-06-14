#ifndef NEBULA_SCENE_UTIL_PARENT_HH
#define NEBULA_SCENE_UTIL_PARENT_HH

#include <Galaxy-Standard/map.hpp>

#include <Nebula/Core/Pose.hh>

#include <Nebula/Scene/Util/Types.hh>
#include <Nebula/Util/parent.hpp>

namespace Neb {
	namespace Scene {
		namespace util {
			class parent:
				public neb::util::parent,
				virtual public neb::core::Pose
			{
				public:
			};
		}
	}
}

#endif

