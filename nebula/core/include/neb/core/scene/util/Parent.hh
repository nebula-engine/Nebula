#ifndef NEBULA_SCENE_UTIL_PARENT_HH
#define NEBULA_SCENE_UTIL_PARENT_HH

#include <Galaxy-Standard/map.hpp>

#include <neb/core/Pose.hh>

#include <neb/core/scene/util/Types.hh>
#include <neb/core/scene/base.hpp>
#include <neb/util/parent.hpp>

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

