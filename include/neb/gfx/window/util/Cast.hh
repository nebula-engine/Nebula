#ifndef NEBULA_GRAPHICS_WINDOW_UTIL_CAST_HH
#define NEBULA_GRAPHICS_WINDOW_UTIL_CAST_HH

#include <neb/util/shared.hpp>
#include <neb/gfx/util/decl.hpp>

namespace neb {
	namespace gfx {
		namespace window {
			namespace util {
				class cast:
					virtual public neb::std::shared
				{
					public:
						sp::shared_ptr<neb::gfx::window::base>		isWindowBase();
				};
			}
		}
	}
}

#endif



