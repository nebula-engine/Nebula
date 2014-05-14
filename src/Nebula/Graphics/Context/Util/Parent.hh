#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH

#include <Nebula/Graphics/Context/Base.hh>

namespace Neb {
	namespace Graphics {
		namespace Context {
			namespace Util {
				class Parent {
					public:
						Neb::Map<Neb::Graphics::Context::Base>          contexts_;
				};
			}
		}
	}
}

#endif
