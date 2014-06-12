#ifndef NEBULA_GRAPHICS_LIGHT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_LIGHT_UTIL_PARENT_HH

#include <Nebula/Core/Pose.hh>
#include <Nebula/Shape/Util/Cast.hh>
#include <Nebula/Graphics/Light/__base.hpp>
#include <Nebula/Util/parent.hpp>

namespace neb {
	namespace Light {
		namespace Util {
			class Parent:
				virtual public neb::Util::parent<neb::core::light::__base>,
				virtual public neb::Shape::Util::Cast,
				virtual public neb::core::Pose
			{
				public:
					virtual ~Parent() {}
			};
		}
	}
}

#endif
