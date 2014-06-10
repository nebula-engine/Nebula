#ifndef NEBULA_SCENE_FLAG
#define NEBULA_SCENE_FLAG

#include <Galaxy-Standard/flag.hpp>

namespace Neb {
	namespace Scene {
		namespace Util {
			DEFINE_FLAG(Flag,
					((RAY_TRACE)		(1 << 1))
					((LIGHTING)		(1 << 2))
					((SHADOW)		(1 << 3))
					((REFLECT)		(1 << 4))
					((REFLECT_PLANAR)	(1 << 5))
					((REFLECT_CURVED)	(1 << 6))
					((TEX_IMAGE)		(1 << 7))
					((TEX_NORMAL_MAP)	(1 << 8))
					((SHADER)		(1 << 9))
				   )
		}
	}
}

#endif
