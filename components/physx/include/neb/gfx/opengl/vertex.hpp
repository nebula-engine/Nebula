#ifndef NEB_GFX_OGL_VERTEX_HPP
#define NEB_GFX_OGL_VERTEX_HPP

#include <gal/stl/helper.hpp>

#include <GL/glew.h>

struct array_type {
	enum e {
		VEC2,
		VEC3,
		VEC4,
		FLOAT
	};
};

template<array_type::e T> struct array_traits {};
template<> struct array_traits<array_type::FLOAT>
{
	static const GLint		size = 1;
	static const GLenum		type = GL_FLOAT;
	static const GLboolean		normalized = GL_FALSE;
	static const long		bytes = 4;
};
template<> struct array_traits<array_type::VEC2>
{
	static const GLint		size = 2;
	static const GLenum		type = GL_FLOAT;
	static const GLboolean		normalized = GL_FALSE;
	static const long		bytes = 8;
};
template<> struct array_traits<array_type::VEC3>
{
	static const GLint		size = 3;
	static const GLenum		type = GL_FLOAT;
	static const GLboolean		normalized = GL_FALSE;
	static const long		bytes = 12;
};
template<> struct array_traits<array_type::VEC4>
{
	static const GLint		size = 4;
	static const GLenum		type = GL_FLOAT;
	static const GLboolean		normalized = GL_FALSE;
	static const long		bytes = 16;
};


namespace neb { namespace gfx { namespace ogl {

	/** @brief vertexAttribPointer
	 *
	 * used by neb::gfx::glsl::buffer::base
	 *
	 */
	template<GLushort ATTRIB_COUNT, array_type::e... A> void		vertexAttribPointer(
			const GLenum		target,
			GLint*			index,
			const GLsizeiptr	stride,
			GLvoid * const *	pointer,
			GLuint			buffer,
			const GLuint*		divisor)
	{
		typedef typename gens<sizeof...(A)>::type seq_t;

		assert(index);
		assert(pointer);
		assert(divisor);

		static_assert(ATTRIB_COUNT == sizeof...(A), "wrong number of template parameters");

		static const GLint size[] = { array_traits<A>::size... };
		GLenum type[] = { array_traits<A>::type... };
		GLboolean normalized[] = { array_traits<A>::normalized... };

		for(unsigned int c = 0; c < ATTRIB_COUNT; c++)
		{
			if(index[c] != -1)
			{
				glBindBuffer(
						target,
						buffer);

				checkerror("glBindBuffer");

				glEnableVertexAttribArray(
						index[c]);

				checkerror("glEnableVertexAttribArray %i\n", index[c]);

				glVertexAttribPointer(
						index[c],
						size[c],
						type[c],
						normalized[c],
						stride,
						(GLvoid*)pointer[c]);

				checkerror("glVertexAttribPointer\nindex %i\nsize %i\nstride %i\npointer %i\n",
						index[c],
						size[c],
						stride,
						pointer[c]);

				glVertexAttribDivisor(
						index[c],
						divisor[c]);

				checkerror("glVertexAttribDivisor");

			}
		}
	}
	void			bufferSubData(
			const GLenum		target,
			GLuint			buffer,
			GLintptr		begin,
			GLintptr		end,
			const GLsizeiptr	datasize,
			GLsizeiptr		size,
			GLvoid* const		data);

	void			bufferData(
			const GLenum		target,
			const GLuint		buffer,
			const GLsizeiptr	datasize,
			const GLsizeiptr	size,
			GLvoid* const		data,
			const GLenum		usage);

	void			bufferDataNull(
			const GLenum		target,
			GLuint			buffer,
			const GLsizeiptr	datasize,
			GLsizeiptr		size,
			const GLenum		usage);

}}}

#endif







