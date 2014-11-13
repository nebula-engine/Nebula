#ifndef NEB_GFX_GLSL_BUFFER_TRAITS_HPP
#define NEB_GFX_GLSL_BUFFER_TRAITS_HPP

#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx { namespace glsl { namespace buffer {

	template<typename BUFFER> struct traits {};
	
/*	template<> struct traits<tri1> {
		enum {
			BUFFER_COUNT = 2,
			ATTRIB_COUNT = 5
		};
	};
	template<> struct traits<instanced> {
		enum {
			BUFFER_COUNT = 7,
			ATTRIB_COUNT = 10
		};
	};
*/
}}}}

#endif
