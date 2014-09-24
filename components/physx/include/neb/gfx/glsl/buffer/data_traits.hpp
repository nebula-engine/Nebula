#ifndef NEB_GFX_GLSL_BUFFER_DATA_TRAITS_HPP
#define NEB_GFX_GLSL_BUFFER_DATA_TRAITS_HPP

#include <neb/gfx/glsl/util/decl.hpp>

namespace math { namespace geo {
	class vertex;
}}

namespace neb { namespace gfx { namespace glsl { namespace buffer {

	template<
		template<typename T, array_type::e... A> class D<T, A...>,
		typename T,
		array_type::e... A
			>
			class data_traits_base
			{



				int		init(neb::gfx::glsl::program::base const * const & p)
				{
						}

				GLint		index_[ATTRIB_COUNT];
				GLuint		buffer_;
			};

	template<> struct data_traits {};



	template<> struct data_traits<math::geo::vertex,>
	{



	};

}}}}

#endif
