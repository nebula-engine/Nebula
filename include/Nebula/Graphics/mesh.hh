#ifndef __GLUTPP_MESH_H__
#define __GLUTPP_MESH_H__

#include <map>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

//#include <galaxy/flag.hpp>

/*
#include <math/vec4.hpp>
#include <math/vec3.hpp>
#include <math/vec2.hpp>
#include <math/transform.hpp>
#include <math/geo/polyhedron.hpp>
*/

#include <Nebula/Math/geo/polyhedron.hh>
#include <Nebula/config.hh>
#include <Nebula/Graphics/material.hh>


namespace Neb {
	struct file_header {
		int len_vertices_;
		int len_indices_;
	};
	struct vertex {
		//void		print();

		glm::vec3		position;
		glm::vec3		normal;
		glm::vec2		texcoor;
	};
	class mesh {
		public:
			mesh();
			void				save(std::string);
			void				load(std::string);
			void				construct(math::geo::polyhedron*);

			// draw data
			file_header			fh_;
			Neb::vertex*			vertices_;
			GLushort*			indices_;
	};
}

#endif
