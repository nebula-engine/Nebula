#ifndef NEB_GFX_GLSL_PROGRAM_UTIL_FLAG_HPP
#define NEB_GFX_GLSL_PROGRAM_UTIL_FLAG_HPP

#include <gal/etc/flag.hpp>

namespace neb { namespace gfx { namespace glsl { namespace program { namespace util {
	DEFINE_FLAG(flag_shader,
			((SHADOW)(1 << 0))
		   )
}}}}}

#endif
