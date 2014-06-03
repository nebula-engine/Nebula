#ifndef NEBULA_GRAPHICS_GUI_OBJECT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_GUI_OBJECT_UTIL_PARENT_HH

#include <Galaxy-Standard/parent.hpp>

#include <Nebula/Graphics/Types.hh>

namespace Neb {
	namespace Graphics {
		namespace GUI {
			namespace Object {
				namespace Util {
					class Parent:
						virtual public gal::std::parent< Neb::Graphics::GUI::Object::Base >
					{

					};
				}
			}
		}
	}
}

#endif

