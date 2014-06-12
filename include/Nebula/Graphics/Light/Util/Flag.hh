#ifndef NEBULA_GRAPHICS_LIGHT_FLAG_HH
#define NEBULA_GRAPHICS_LIGHT_FLAG_HH

#include <Galaxy-Standard/flag.hpp>

namespace neb {
	namespace Light {
		namespace Util {
			DEFINE_FLAG(Flag,
					((SHOULD_RELEASE)(1 << 0))
				   )
		}
	}
}

#endif
