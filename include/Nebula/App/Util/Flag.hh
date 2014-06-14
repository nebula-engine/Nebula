#ifndef NEBULA_APP_UTIL_FLAG_HH
#define NEBULA_APP_UTIL_FLAG_HH

#include <Galaxy-Standard/flag.hpp>

namespace neb {
	namespace App {
		namespace util {
			DEFINE_FLAG(Flag,
					((SHOULD_RELEASE)	(1 << 0))
					((INIT_GLEW)		(1 << 1))
				   )
		}
	}
}

#endif
