#ifndef NEBULA_SHAPE_UTIL_FLAG_HH
#define NEBULA_SHAPE_UTIL_FLAG_HH

#include <Nebula/Enum.hh>

namespace Neb {
	namespace Shape {
		namespace Util {
			DEFINE_FLAG(Flag,
					((FOO)(1 << 0))
				   )
		}
	}
}

#endif
