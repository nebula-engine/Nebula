#ifndef NEBULA_SCENE_FLAG
#define NEBULA_SCENE_FLAG

#include <gal/etc/flag.hpp>

namespace neb { namespace core { namespace core { namespace scene { namespace util {
	DEFINE_FLAG(flag,
			((PHYSX_VISUALIZATION)		(1 << 1))
			((LIGHTING)			(1 << 2))
			((SHADOW)			(1 << 3))
			((REFLECT)		(1 << 4))
			((REFLECT_PLANAR)	(1 << 5))
			((REFLECT_CURVED)	(1 << 6))
			((TEX_IMAGE)		(1 << 7))
			((TEX_NORMAL_MAP)	(1 << 8))
			((SHADER)		(1 << 9))
		   )
}}}}}

#endif
