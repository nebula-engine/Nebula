#ifndef NEBULA_GRAPHICS_GUI_OBJECT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_GUI_OBJECT_UTIL_PARENT_HH

#include <Nebula/Util/parent.hpp>
#include <Nebula/Graphics/Types.hh>

namespace neb {
	namespace gfx {
		namespace gui {
			namespace object {
				namespace Util {
					class Parent:
						virtual public neb::Util::parent<neb::gfx::gui::object::Base>
					{

					};
				}
			}
		}
	}
}

#endif

