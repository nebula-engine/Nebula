#ifndef NEBULA_GRAPHICS_LIGHT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_LIGHT_UTIL_PARENT_HH

#include <Nebula/Core/Pose.hh>

#include <Galaxy-Standard/parent.hpp>

#include <Nebula/Shape/Util/Cast.hh>

namespace Neb {
	namespace Light {
		namespace Util {
			class Parent:
				virtual public gal::std::parent< Neb::Light::Base >,
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
