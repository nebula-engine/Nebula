#ifndef NEBULA_GRAPHICS_WINDOW_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_WINDOW_UTIL_PARENT_HH

namespace Neb {
	namespace Graphics {
		namespace Window {
			namespace Util {
				class Parent {
					public:
						void					insertWindow(Neb::Graphics::Window::Base_s);
						
						Neb::Map<Neb::Graphics::Window::Base>   windows_;
				};
			}
		}
	}
}

#endif
