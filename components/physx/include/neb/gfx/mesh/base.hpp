#ifndef NEB_GFX_CORE_BUFFER_BASE_HPP
#define NEB_GFX_CORE_BUFFER_BASE_HPP

#include <iomanip>
#include <map>

#include <glm/gtx/transform.hpp>

#include <GL/glew.h>

#include <neb/core/pose.hpp>

#include <neb/gfx/free.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/opengl/vertex.hpp>
#include <neb/gfx/opengl/uniform.hpp>
#include <neb/gfx/glsl/buffer/traits.hpp>
#include <neb/gfx/glsl/program/base.hpp>

template<typename T> struct index_traits {};

template<> struct index_traits<GLubyte>
{
	static const GLenum	type = GL_UNSIGNED_BYTE;
};
template<> struct index_traits<GLushort>
{
	static const GLenum	type = GL_UNSIGNED_SHORT;
};
template<> struct index_traits<GLuint>
{
	static const GLenum	type = GL_UNSIGNED_INT;
};

namespace neb { namespace gfx { namespace mesh {

	template<typename... BUFFERS> class base
	{
		public:
			typedef neb::gfx::glsl::program::base		P;
			typedef std::tuple<BUFFERS*...>			buffer_tuple;
			typedef std::map<P const *, buffer_tuple>	program_buffer_map;

			enum {
				BUFFER_COUNT = sizeof...(BUFFERS)
			};
			typedef typename gens<BUFFER_COUNT>::type seq_type;

		protected:
		public:

			virtual GLsizeiptr*		begin() = 0;
			virtual GLsizeiptr*		end() = 0;
			virtual GLsizeiptr*		size() = 0;
			virtual GLsizeiptr*		size_array() = 0;
			virtual GLvoid** const		data() = 0;

			template<int I> GLsizeiptr		begin()		{ begin(); return begin_[I]; }
			template<int I> GLsizeiptr		end()		{ end(); return end_[I]; }
			template<int I> GLsizeiptr		size()		{ size(); return size_[I]; }
			template<int I> GLsizeiptr		size_array()	{ size_array(); return size_array_[I]; }
			template<int I> GLvoid* const		data()		{ data(); return data_[I]; }

			/** set by function of same name then sent to bufferData functions */
			GLvoid*				data_[BUFFER_COUNT];
			GLsizeiptr			begin_[BUFFER_COUNT];
			GLsizeiptr			end_[BUFFER_COUNT];
			GLsizeiptr			size_[BUFFER_COUNT];
			GLsizeiptr			size_array_[BUFFER_COUNT];

			

			void					bufferData(buffer_tuple const & bt) { bufferData(seq_type(), bt); }
			template<int...S> void			bufferData(seq<S...>, buffer_tuple const & bt) {
				pass((
							std::get<S>(bt)->bufferData(
								size<S>(),
								data<S>()
								)
							)...);
			}
			void					bufferDataNull(buffer_tuple const & bt) { bufferDataNull(seq_type(), bt); }
			template<int...S> void			bufferDataNull(seq<S...>, buffer_tuple const & bt) {
				pass((
							std::get<S>(bt)->bufferDataNull(
								size_array<S>()
								)
							)...);
			}
			void					bufferSubData(buffer_tuple const & bt) { bufferSubData(seq_type(), bt); }
			template<int...S> void			bufferSubData(seq<S...>, buffer_tuple const & bt) {
				pass((
							std::get<S>(bt)->bufferSubData(
								size<S>(),
								begin<S>(),
								end<S>(),
								data<S>()
								)
				     )...);
			}

		public:
			buffer_tuple				getBufferTuple(P const * const & p)
			{
				auto it = buffers_.find(p);

				if(it == buffers_.end())
				{
					buffer_tuple bt(getBuffer<BUFFERS>(p)...);

					bufferData(bt);

					buffers_[p] = bt;

					return bt;
				}

				return it->second;
			}
			template<typename BUFFER> BUFFER*	getBuffer(neb::gfx::glsl::program::base const * const & p)
			{
				BUFFER* b = new BUFFER();
				b->init(p);
				return b;
			}
		public:
			void				vertexAttribPointer(buffer_tuple const & bt) { vertexAttribPointer(seq_type(), bt); }
			template<int...S> void		vertexAttribPointer(seq<S...>, buffer_tuple const & bt) { pass((std::get<S>(bt)->vertexAttribPointer())...); }
			void				bind(buffer_tuple const & bt) { vertexAttribPointer(seq_type(), bt); }
			template<int...S> void		bind(seq<S...>, buffer_tuple const & bt) { pass((std::get<S>(bt)->vertexAttribPointer())...); }
			void				unbind(buffer_tuple const & bt) { vertexAttribPointer(seq_type(), bt); }
			template<int...S> void		unbind(seq<S...>, buffer_tuple const & bt) { pass((std::get<S>(bt)->vertexAttribPointer())...); }

		private:
			program_buffer_map			buffers_;


	};

	template<typename... BUFFERS> class elements: public base<BUFFERS...>
	{
		public:

			typedef base<BUFFERS...>	B;

			using B::getBufferTuple;
			using B::bind;
			using B::unbind;
			using B::vertexAttribPointer;

			typedef neb::gfx::glsl::program::base		P;
			typedef std::tuple<BUFFERS*...>			buffer_tuple;
			typedef std::map<P const *, buffer_tuple>	program_buffer_map;

			enum {
				BUFFER_COUNT = sizeof...(BUFFERS)
			};
			typedef typename gens<BUFFER_COUNT>::type seq_type;

		protected:
			void			drawElements(
					neb::gfx::glsl::program::base const * const & p,
					neb::core::pose const & pose,
					glm::vec3 scale,
					GLsizei count)
			{

				assert(p);

				buffer_tuple bt = getBufferTuple(p);

				drawElements(p, bt, pose, scale, count);

			}
			void			drawElements(
					neb::gfx::glsl::program::base const * const &	p,
					buffer_tuple const &				bt,
					neb::core::pose const &				pose,
					glm::vec3					scale,
					GLsizei						count)
			{
				LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

				vertexAttribPointer(bt);

				// load modelview matrix
				LOG(lg, neb::gfx::sl, debug) << "load modelview matrix";
				glm::mat4 model = pose.mat4_cast() * glm::scale(scale);

				assert(p->uniform_table_[neb::gfx::glsl::uniforms::MODEL] != -1);

				neb::gfx::ogl::glUniform(
						p->uniform_table_[neb::gfx::glsl::uniforms::MODEL],
						model
						);

				// bind
				LOG(lg, neb::gfx::sl, debug) << "bind vbo";
				bind(bt);

				checkerror("unknown");

				// draw
				LOG(lg, neb::gfx::sl, debug) << "draw";
				glDrawElements(
						GL_TRIANGLES,
						count,
						GL_UNSIGNED_SHORT,
						0);

				checkerror("glDrawElements\ncount %i\n", count);

				// unbind
				LOG(lg, neb::gfx::sl, debug) << "unbind vbo";
				unbind(bt);
			}


	};

}}}

#endif
