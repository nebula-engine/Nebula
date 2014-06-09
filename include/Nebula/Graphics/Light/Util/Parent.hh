#ifndef NEBULA_GRAPHICS_LIGHT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_LIGHT_UTIL_PARENT_HH

#include <Nebula/Core/Pose.hh>
#include <Nebula/Shape/Util/Cast.hh>
#include <Nebula/Util/parent.hpp>

namespace Neb {
	namespace Light {
		namespace Util {
			class Parent:
				public Neb::Util::parent,
				virtual public Neb::Shape::Util::Cast,
				virtual public Neb::Core::Pose
			{
				public:
					virtual ~Parent() {}
			};
		}
	}
}

#endif
