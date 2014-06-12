#ifndef NEBULA_GRAPHICS_WINDOW_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_WINDOW_UTIL_PARENT_HH

#include <Nebula/Util/parent.hpp>
#include <Nebula/Graphics/Window/__base.hpp>

namespace neb {
	namespace gfx {
		namespace Window {
			namespace Util {
				class Parent:
					public Neb::Util::parent<Neb::Graphics::Window::__base>
				{
					public:
				};
			}
		}
	}
}

#endif

