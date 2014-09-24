#ifndef NEB_GFX_GLSL_BUFFER_BASE_HPP
#define NEB_GFX_GLSL_BUFFER_BASE_HPP

#include <gal/stl/helper.hpp>

#include <neb/gfx/free.hpp>
#include <neb/gfx/opengl/vertex.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/glsl/buffer/traits.hpp>
#include <neb/gfx/glsl/program/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace buffer {


	template< array_type::e... > class templ;
		
	/** @brief base
	 *
	 * derived classes must implement
	 * stride_[BUFFER_COUNT]
	 * target_[BUFFER_COUNT]
	 * pointer_[ATTRIB_COUNT]
	 */
	//template< template< array_type::e... A > class D_, array_type::e... A > class base
	//template< class D_, array_type::e... A > class base;

	template< class D_ > class __base
	{
		public:
			typedef D_ D;

			int		bufferData(
					GLsizeiptr size,
					GLvoid* const data)
			{
				neb::gfx::ogl::bufferData(
						D::target_,
						buffer_,
						sizeof(typename D::data_type),
						size,
						(GLvoid** const)data,
						D::usage_
						);
				return 0;
			}
			int		bufferSubData(
					GLsizeiptr begin,
					GLsizeiptr end,
					GLsizeiptr size,
					GLvoid* const data)
			{

				//LOG(lg, neb::gfx::sl, debug) << "update " << b << " to " << e;

				neb::gfx::ogl::bufferSubData(
						D::target_,
						buffer_,
						begin,
						end,
						sizeof(typename D::data_type),
						size,
						(GLvoid* const)data
						);
				return 0;
			}
			int		bufferDataNull(
					GLsizeiptr size_array)
			{

				neb::gfx::ogl::bufferDataNull(
						D::target_,
						buffer_,
						sizeof(typename D::data_type),
						size_array,
						D::usage_
						);
				return 0;
			}

			int		bind()
			{
				glBindBuffer(D::target_, buffer_);
				checkerror("glBindBuffer");
				return 0;
			}
			int		unbind()
			{
				glBindBuffer(D::target_, 0);
				checkerror("glBindBuffer");
				return 0;
			}

			GLuint			buffer_;

	};

	template< class D_ > class base;

	template< array_type::e... A > class base< templ<A...> >: public __base< templ<A...> >
	{
		public:
			typedef templ<A...> D;

			using __base<D>::buffer_;

			//static_assert(traits<BUFFER>::ATTRIB_COUNT == sizeof...(A), "wrong number of template parameters");

			enum {
				ATTRIB_COUNT = sizeof...(A)
			};

			base() {}
			int		init(neb::gfx::glsl::program::base const * const & p)
			{
				glGenBuffers(1, &buffer_);
				checkerror("glGenBuffers");

				for(int i = 0; i < ATTRIB_COUNT; i++)
				{
					index_[i] = p->attrib_table_[D::attribute_[i]];
				}
				return 0;
			}
		public:
			int		vertexAttribPointer()
			{
				neb::gfx::ogl::vertexAttribPointer<ATTRIB_COUNT, A...>
					(
					 D::target_,
					 index_,
					 sizeof(typename D::data_type),
					 D::pointer_,
					 buffer_,
					 D::divisor_
					);

				return 0;
			}
			GLint			index_[ATTRIB_COUNT];
	};




	template<typename T> class elements: public __base< elements<T> >
	{
		public:
			using __base< elements<T> >::buffer_;

			typedef T data_type;

			static const GLenum	target_	= GL_ELEMENT_ARRAY_BUFFER;
			static const GLenum	usage_	= GL_STATIC_DRAW;

			int		init(neb::gfx::glsl::program::base const * const & p)
			{
				glGenBuffers(1, &buffer_);
				checkerror("glGenBuffers");
				return 0;
			}

			int		vertexAttribPointer() { return 0; }

	};




}}}}

#endif
