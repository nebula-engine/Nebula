#ifndef NEBULA_GRAPHICS_WINDOW_UTIL_CAST_HH
#define NEBULA_GRAPHICS_WINDOW_UTIL_CAST_HH

#include <neb/core/itf/shared.hpp>

#include <neb/gfx/util/decl.hpp>

namespace neb {
	namespace gfx {
		namespace window {
			namespace util {
				class cast:
					virtual public neb::itf::shared
				{
					public:
						std::shared_ptr<neb::gfx::window::base>		isWindowBase();
				};
			}
		}
	}
}

#endif



