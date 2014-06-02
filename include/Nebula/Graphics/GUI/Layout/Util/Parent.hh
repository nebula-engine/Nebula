#ifndef NEBULA_GRAPHICS_GUI_LAYOUT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_GUI_LAYOUT_UTIL_PARENT_HH

#include <Galaxy-Standard/parent.hpp>

#include <Nebula/Graphics/GUI/Layout/Types.hh>

namespace Neb {
	namespace Graphics {
		namespace GUI {
			namespace Layout {
				namespace Util {
					class Parent: virtual public Neb::Util::Parent<Neb::Graphics::GUI::Layout::Base> {
						public:
							Neb::Graphics::Window::Base_s			getWindow();
					};
				}
			}
		}
	}
}

#endif
