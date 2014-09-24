#ifndef NEB_GFX_MESH_INSTANCED_HPP
#define NEB_GFX_MESH_INSTANCED_HPP

#include <neb/gfx/mesh/base.hpp>
#include <neb/gfx/mesh/tri1.hpp>

#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/util/array_continuous.hpp>

#include <neb/gfx/glsl/buffer/instanced.hpp>


namespace neb { namespace gfx { namespace mesh {

	class instanced: public neb::gfx::mesh::base<neb::gfx::glsl::buffer::instanced>
	{
		public:
			typedef neb::gfx::glsl::program::base			program_type;
			typedef std::shared_ptr<program_type>			program_shared;
			typedef neb::gfx::glsl::buffer::instanced		buffer_type;
			typedef std::shared_ptr<buffer_type>			buffer_shared;
			typedef std::map<program_type*, buffer_shared>		buffer_map;

			typedef neb::gfx::array_continuous<
				glm::mat4,
				glm::vec4,
				unsigned int,
				glm::vec4,
				glm::vec4,
				glm::vec4,
				float
				>		instances_type;
			typedef instances_type::slot_type			slot_type;
			
			typedef neb::gfx::mesh::base<neb::gfx::glsl::buffer::instanced>		B;
			
			typedef neb::gfx::glsl::program::base		P;
			typedef typename B::buffer_tuple		buffer_tuple;
			typedef std::map<P const *, buffer_tuple>	program_buffer_map;

			enum {
				BUFFER_COUNT = B::BUFFER_COUNT
			};
			typedef typename gens<BUFFER_COUNT>::type seq_type;



		public:
			void							init(program_type*);
			virtual GLsizeiptr*					begin();
			virtual GLsizeiptr*					end();
			virtual GLsizeiptr*					size_array();
			virtual GLsizeiptr*					size();
			virtual GLvoid** const					data();

			void							draw(program_type*);
			void							draw(program_type*, buffer_shared);
		public:
			neb::gfx::mesh::tri1					mesh_;
			
			buffer_map						buffers_;

			std::shared_ptr<instances_type>				instances_;
	};
}}}

#endif

