#ifndef __GLUTPP_MESH_H__
#define __GLUTPP_MESH_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

//#include <galaxy/flag.hpp>

/*
#include <math/vec4.hpp>
#include <math/vec3.hpp>
#include <math/vec2.hpp>
#include <math/transform.hpp>
#include <math/geo/polyhedron.hpp>
*/

#include <neb/core/pose.hpp>
#include <neb/core/math/geo/decl.hpp>

#include <neb/gfx/material.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/buffer/tri1.hpp>
#include <neb/gfx/Context/Util/decl.hpp>
#include <neb/gfx/mesh/base.hpp>

namespace ba = boost::archive;

namespace neb { namespace gfx { namespace mesh {

	class tri1: public elements<neb::gfx::glsl::buffer::elements<GLushort>, neb::gfx::glsl::buffer::tri1>
	{
		public:
			//typedef std::map<neb::gfx::glsl::program::base*, buffer*>	program_buffer_map;

			typedef neb::gfx::glsl::buffer::tri1				buffer;
			typedef neb::gfx::glsl::program::base				program;
			typedef elements<neb::gfx::glsl::buffer::elements<GLushort>, neb::gfx::glsl::buffer::tri1>	base_t;
		
			typedef GLushort index_type;

			tri1();
			~tri1();

			virtual GLsizeiptr*		begin() {
				begin_[0] = 0;
				begin_[1] = 0;
				return begin_;
			}
			virtual GLsizeiptr*		end() {
				begin_[0] = nbVerts_;
				begin_[1] = nbIndices_;
				return begin_;
			}
			virtual GLvoid** const		data() {
				data_[0] = &vertices_[0];
				data_[1] = &indices_[0];
				return data_;
			}
			GLsizeiptr*			size_array() {
				return size();
			}
			GLsizeiptr*			size() {
				assert(!nbVerts_ == 0);
				assert(!nbIndices_ == 0);
				
				size_[0] = nbVerts_;
				size_[1] = nbIndices_;
				return size_;
			}

			void				serialize(
					ba::polymorphic_iarchive & ar, unsigned int const & version);
			void				serialize(
					ba::polymorphic_oarchive & ar, unsigned int const & version);

			void				construct(math::geo::polyhedron*);
			void				print(int sl);

			/*		
					void				init_buffer(
					program* p);
					void				draw_elements(
					program* p,
					buffer_shared,
					neb::core::pose const & pose,
					glm::vec3 scale);
					*/
			/**
			 * do specific things like custom uniforms, then call mesh::base::drawElements
			 */
			void				drawDebug(
					program const * const & p,
					neb::core::pose const & pose,
					glm::vec3 scale);
			void				drawElements(
					program const * const & p,
					neb::core::pose const & pose,
					glm::vec3 scale);


			neb::material::material			material_front_;


			void					setVerts(math::geo::vertex*, GLuint);
			void					setIndices(index_type*, GLuint);
			GLuint					getNbVerts();
			GLuint					getNbIndices();
		private:
			math::geo::vertex*				vertices_;
			index_type*					indices_;
			GLuint						nbVerts_;
			GLuint						nbIndices_;
		public:


			std::shared_ptr<neb::gfx::texture>		texture_;
			std::shared_ptr<neb::gfx::texture>		normal_map_;
	};
}}}

#endif


