#ifndef NEBULA_GRAPHICS_WINDOW_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_WINDOW_UTIL_PARENT_HH

#include <Nebula/Util/parent.hpp>
#include <Nebula/Graphics/Window/__base.hpp>

namespace neb {
	namespace gfx {
		namespace window {
			namespace util {
				class parent:
					public neb::util::parent<neb::gfx::window::__base>
				{
					public:
				};
			}
		}
	}
}

#endif

