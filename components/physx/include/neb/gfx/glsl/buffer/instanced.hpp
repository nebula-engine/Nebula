#ifndef NEB_GFX_GLSL_BUFFER_MESH_INSTANCED_HPP
#define NEB_GFX_GLSL_BUFFER_MESH_INSTANCED_HPP

#include <memory>

#include <GL/glew.h>

#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/glsl/buffer/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace buffer {

	struct inst_data
	{
		glm::mat4	model_;
		glm::vec4	a_;
		glm::vec4	b_;
		glm::vec4	c;
		glm::vec4	d;
		glm::vec4	e;
		GLfloat	f;
	};

	typedef templ<array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::FLOAT> instanced;

	template<> class templ<array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::FLOAT>:
			public neb::gfx::glsl::buffer::base<
			templ<
			array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::VEC4,
		array_type::FLOAT > >
		{
			public:
				typedef std::shared_ptr<neb::gfx::glsl::program::base>		program_shared;
				typedef neb::gfx::glsl::buffer::base<instanced>			buffer_base_type;

				//static const glm::mat4 m;
				static const GLenum		usage_	= GL_STREAM_DRAW;
				static const GLenum		target_	= GL_ARRAY_BUFFER;

				typedef inst_data data_type;

				static constexpr GLuint		divisor_[ATTRIB_COUNT] = {
					1,1,1,
					1,1,1,
					1,1,1,
					1
				};
				static constexpr void*		pointer_[ATTRIB_COUNT] = {
					(void*)0,
					(void*)16,
					(void*)32,
					(void*)48,
					(void*)64,
					(void*)80,
					(void*)96,
					(void*)112,
					(void*)128,
					(void*)144
				};
				static constexpr neb::gfx::glsl::attribs::e	attribute_[ATTRIB_COUNT] = {
					neb::gfx::glsl::attribs::INSTANCE_MODEL0,
					neb::gfx::glsl::attribs::INSTANCE_MODEL1,
					neb::gfx::glsl::attribs::INSTANCE_MODEL2,
					neb::gfx::glsl::attribs::INSTANCE_MODEL3,
					neb::gfx::glsl::attribs::INSTANCE_SAMPLER,
					neb::gfx::glsl::attribs::INSTANCE_DIFFUSE,
					neb::gfx::glsl::attribs::INSTANCE_AMBIENT,
					neb::gfx::glsl::attribs::INSTANCE_SPECULAR,
					neb::gfx::glsl::attribs::INSTANCE_EMISSION,
					neb::gfx::glsl::attribs::INSTANCE_SHININESS
				};


			public:

		};
}}}}

#endif


