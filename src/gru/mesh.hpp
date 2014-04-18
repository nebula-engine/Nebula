#ifndef __GLUTPP_MESH_H__
#define __GLUTPP_MESH_H__

#include <map>

#include <GLFW/glfw3.h>

#include <gal/flag.h>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/transform.h>
#include <math/geo/polyhedron.h>

#include <gru/config.hpp>
#include <gru/shape/desc.hpp>
#include <gru/material.hpp>

namespace glutpp
{
	struct file_header
	{
		int len_vertices_;
		int len_indices_;
	};
	struct vertex
	{
		//void		print();

		math::vec4	position;
		math::vec3	normal;
		math::vec2	texcoor;
	};
	class mesh
	{
		public:
			mesh();
			void				save(char const *);
			void				load(char const *);
			void				construct(math::geo::polyhedron*);

			// draw data
			file_header			fh_;
			glutpp::vertex*			vertices_;
			GLushort*			indices_;
	};
}

#endif
