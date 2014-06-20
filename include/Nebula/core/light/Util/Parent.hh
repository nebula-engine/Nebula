#ifndef NEBULA_GRAPHICS_LIGHT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_LIGHT_UTIL_PARENT_HH

#include <Nebula/core/Pose.hh>
#include <Nebula/core/shape/Util/Cast.hh>
#include <Nebula/core/light/__base.hpp>
#include <Nebula/util/parent.hpp>

namespace neb {
	namespace Light {
		namespace util {
			class parent:
				virtual public neb::util::parent<neb::core::light::__base>,
				virtual public neb::core::shape::util::cast,
				virtual public neb::core::Pose
			{
				public:
					virtual ~parent() {}
			};
		}
	}
}

#endif
