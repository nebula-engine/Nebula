#ifndef NEBULA_GRAPHICS_LIGHT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_LIGHT_UTIL_PARENT_HH

#include <Nebula/Util/Parent.hh>
#include <Nebula/Shape/Util/Cast.hh>

namespace Neb {
	namespace Light {
		namespace Util {
			class Parent:
				virtual public Neb::Util::Parent<Neb::Light::Base>,
				virtual public Neb::Shape::Util::Cast
			{
				public:
					virtual ~Parent() {}
			};
		}
	}
}

#endif
