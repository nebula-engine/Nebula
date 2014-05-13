#ifndef NEBULA_GRAPHICS_LIGHT_FLAG_HH
#define NEBULA_GRAPHICS_LIGHT_FLAG_HH

#include <Nebula/Enum.hh>

namespace Neb {
	namespace Light {
		namespace Util {
			DEFINE_FLAG(Flag,
					((SHOULD_RELEASE)(1 << 0))
				   )
		}
	}
}

#endif
