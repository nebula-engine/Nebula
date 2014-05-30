#ifndef NEBULA_GRAPHICS_WINDOW_UTIL_CAST_HH
#define NEBULA_GRAPHICS_WINDOW_UTIL_CAST_HH

#include <Nebula/Util/Shared.hh>
#include <Nebula/Graphics/Types.hh>

namespace Neb {
	namespace Graphics {
		namespace Window {
			namespace Util {
				class Cast:
					virtual public Neb::Util::Shared
				{
					public:
						Neb::Graphics::Window::Base_s		isWindowBase();
				};
			}
		}
	}
}

#endif



