#ifndef NEBULA_GFX_CAMERA_VIEW_UTIL_FLAG_HPP
#define NEBULA_GFX_CAMERA_VIEW_UTIL_FLAG_HPP

#include <Galaxy-Standard/flag.hpp>

namespace neb { namespace gfx { namespace camera { namespace view { namespace util {

	DEFINE_FLAG(flag,
			((WEST)		(1 << 0))
			((EAST)		(1 << 1))
			((SOUTH)	(1 << 2))
			((NORTH)	(1 << 3))
			((DOWN)		(1 << 4))
			((UP)		(1 << 5))
			((YAW_POS)	(1 << 6))
			((YAW_NEG)	(1 << 7))
			((PITCH_POS)	(1 << 8))
			((PITCH_NEG)	(1 << 9))
		   )


}}}}}

#endif
