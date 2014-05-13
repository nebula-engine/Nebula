#ifndef NEBULA_GRAPHICS_LIGHT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_LIGHT_UTIL_PARENT_HH

#include <Nebula/Shape/Util/Cast.hh>

namespace Neb {
	namespace Light {
		namespace Util {
			class Parent:
				public Neb::Shape::Util::Cast
			{
				public:
					Parent();
					virtual ~Parent() {}
					
					
					Neb::Map<Neb::Light::Base>
			};
		}
	}
}

#endif
