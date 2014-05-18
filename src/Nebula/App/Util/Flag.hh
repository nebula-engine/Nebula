#ifndef NEBULA_APP_UTIL_FLAG_HH
#define NEBULA_APP_UTIL_FLAG_HH

#include <Nebula/Enum.hh>

namespace Neb {
	namespace App {
		namespace Util {
			DEFINE_FLAG(Flag,
					((SHOULD_RELEASE)	(1 << 0))
				   )
		}
	}
}

#endif
