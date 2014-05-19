#ifndef NEBULA_GRAPHICS_WINDOW_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_WINDOW_UTIL_PARENT_HH

#include <Nebula/Util/Parent.hh>

namespace Neb {
	namespace Graphics {
		namespace Window {
			namespace Util {
				class Parent: virtual public Neb::Util::Parent<Neb::Graphics::Window::Base> {
					public:
				};
			}
		}
	}
}

#endif
