#ifndef NEB_GFX_GLSL_BUFFER_MESH_HPP
#define NEB_GFX_GLSL_BUFFER_MESH_HPP

#include <memory>

#include <GL/glew.h>

#include <neb/core/math/geo/vertex.hpp>

#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/glsl/buffer/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace buffer {


	template<array_type::e...> class templ {};

	typedef templ<array_type::VEC3,array_type::VEC3,array_type::VEC2,array_type::VEC3,array_type::VEC3> tri1;

	template<> class templ<array_type::VEC3,array_type::VEC3,array_type::VEC2,array_type::VEC3,array_type::VEC3>: 
		public neb::gfx::glsl::buffer::base< templ<array_type::VEC3,array_type::VEC3,array_type::VEC2,array_type::VEC3,array_type::VEC3> >
		{
			public:
				typedef std::shared_ptr<neb::gfx::glsl::program::base> program_shared;


				static const GLenum			target_	= GL_ARRAY_BUFFER;
				static const GLenum			usage_	= GL_STATIC_DRAW;

				typedef math::geo::vertex data_type;

				static constexpr GLuint			divisor_[ATTRIB_COUNT] = {
					0,0,0,0,0
				};

				static constexpr GLvoid*			pointer_[ATTRIB_COUNT] = {
					(GLvoid*)0,
					(GLvoid*)12,
					(GLvoid*)24,
					(GLvoid*)32,
					(GLvoid*)44
				};

				static constexpr neb::gfx::glsl::attribs::e	attribute_[ATTRIB_COUNT] = {
					neb::gfx::glsl::attribs::POSITION,
					neb::gfx::glsl::attribs::NORMAL,
					neb::gfx::glsl::attribs::TEXCOOR,
					neb::gfx::glsl::attribs::TANGENT,
					neb::gfx::glsl::attribs::BINORMAL
				};
		};
}}}}

#endif

