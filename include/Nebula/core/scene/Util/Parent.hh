#ifndef NEBULA_SCENE_UTIL_PARENT_HH
#define NEBULA_SCENE_UTIL_PARENT_HH

#include <Galaxy-Standard/map.hpp>

#include <Nebula/core/Pose.hh>

#include <Nebula/core/scene/Util/Types.hh>
#include <Nebula/core/scene/Base.hh>
#include <Nebula/util/parent.hpp>

namespace neb { namespace core {
	namespace scene {
		namespace util {
			class parent:
				virtual public neb::util::parent<neb::core::scene::base>,
				virtual public neb::core::Pose
			{
				public:
			};
		}
	}
}}

#endif

