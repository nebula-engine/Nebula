#ifndef NEBULA_GRAPHICS_GUI_OBJECT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_GUI_OBJECT_UTIL_PARENT_HH

#include <neb/util/parent.hpp>
#include <neb/gfx/util/decl.hpp>

namespace neb {
	namespace gfx {
		namespace gui {
			namespace object {
				namespace util {
					class parent:
						virtual public neb::util::parent<neb::gfx::gui::object::base>
					{

					};
				}
			}
		}
	}
}

#endif

