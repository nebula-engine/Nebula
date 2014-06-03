#ifndef NEBULA_GRAPHICS_WINDOW_UTIL_CAST_HH
#define NEBULA_GRAPHICS_WINDOW_UTIL_CAST_HH

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/Graphics/Types.hh>

namespace Neb {
	namespace Graphics {
		namespace Window {
			namespace Util {
				class Cast:
					virtual public gal::std::shared
				{
					public:
						Neb::Graphics::Window::Base_s		isWindowBase();
				};
			}
		}
	}
}

#endif



