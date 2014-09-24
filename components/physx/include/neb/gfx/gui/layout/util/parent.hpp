#ifndef NEBULA_GRAPHICS_GUI_LAYOUT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_GUI_LAYOUT_UTIL_PARENT_HH

#include <neb/core/util/parent.hpp>

#include <neb/gfx/gui/layout/base.hpp>

namespace neb {
	namespace gfx {
		namespace gui {
			namespace layout {
				namespace util {
					class parent:
						public neb::util::parent<neb::gfx::gui::layout::base, parent>
					{
						public:
					};
				}
			}
		}
	}
}

#endif
