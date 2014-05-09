#ifndef NEBULA_SHAPE_TYPE
#define NEBULA_SHAPE_TYPE

#include <Nebula/Enum.hpp>

namespace Neb {
	namespace Shape {
		DEFINE_TYPE(Type,
				((BASE)(1))
				((BOX)(2))
				((SPHERE)(3))
				((EMPTY)(4))
			   )
	}
}

#endif
