#ifndef NEBULA_SHAPE_UTIL_FLAG_HH
#define NEBULA_SHAPE_UTIL_FLAG_HH

#include <Nebula/Enum.hh>

namespace Neb {
	namespace shape {
		namespace util {
			DEFINE_FLAG(Flag,
					((FOO)(1 << 0))
				   )
		}
	}
}

#endif
