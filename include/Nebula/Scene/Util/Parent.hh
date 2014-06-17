#ifndef NEBULA_SCENE_UTIL_PARENT_HH
#define NEBULA_SCENE_UTIL_PARENT_HH

#include <Galaxy-Standard/map.hpp>

#include <Nebula/Core/Pose.hh>

#include <Nebula/Scene/Util/Types.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Util/parent.hpp>

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

