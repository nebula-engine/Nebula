#ifndef NEBULA_GRAPHICS_WINDOW_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_WINDOW_UTIL_PARENT_HH

#include <Galaxy-Standard/parent.hpp>

namespace Neb {
	namespace Graphics {
		namespace Window {
			namespace Util {
				class Parent: virtual public Neb::Util::parent< Neb::Graphics::Window::Base > {
					public:
				};
			}
		}
	}
}

#endif

