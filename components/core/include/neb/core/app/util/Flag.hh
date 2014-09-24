#ifndef NEBULA_APP_UTIL_FLAG_HH
#define NEBULA_APP_UTIL_FLAG_HH

#include <gal/etc/flag.hpp>

namespace neb {
	namespace core {
		namespace app {
			namespace util {
				DEFINE_FLAG(flag,
					((SHOULD_RELEASE)(1 << 0))
					((INIT___BASE)(1 << 1))
					((INIT_GLEW)(1 << 2))
					((INIT_GLFW)(1 << 3))
					)
			}
		}
	}
}

#endif
