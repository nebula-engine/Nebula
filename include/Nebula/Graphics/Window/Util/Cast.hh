#ifndef NEBULA_GRAPHICS_WINDOW_UTIL_CAST_HH
#define NEBULA_GRAPHICS_WINDOW_UTIL_CAST_HH

#include <Nebula/Util/shared.hpp>
#include <Nebula/Graphics/Types.hh>

namespace neb {
	namespace gfx {
		namespace Window {
			namespace Util {
				class Cast:
					virtual public neb::std::shared
				{
					public:
						neb::gfx::Window::Base_s		isWindowBase();
				};
			}
		}
	}
}

#endif



