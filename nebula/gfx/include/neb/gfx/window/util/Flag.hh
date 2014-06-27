#ifndef NEBULA_GRAPHICS_WINDOW_uTIL_FLAG_HH
#define NEBULA_GRAPHICS_WINDOW_uTIL_FLAG_HH

#include <Galaxy-Standard/flag.hpp>

namespace neb {
	namespace gfx {
		namespace window {
			namespace util {
				DEFINE_FLAG(Flag,
						((SHOULD_RELEASE)(1 << 0))
					   )
			}
		}
	}
}

#endif

