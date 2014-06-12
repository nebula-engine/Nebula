#ifndef __GLUTPP_MESH_H__
#define __GLUTPP_MESH_H__

#include <map>

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

#include <Nebula/Math/geo/decl.hpp>

#include <Nebula/config.hh>
#include <Nebula/Graphics/material.hh>


namespace neb {
	struct file_header {
		int len_vertices_;
		int len_indices_;
	};
	class mesh {
		public:
			mesh();
<<<<<<< HEAD

			void				serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
			void				serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version);
			
			void				construct(math::geo::polyhedron*);
			void				print(int sl);
			
			std::vector<math::geo::vertex>		vertices_;
			std::vector<GLushort>			indices_;
=======
			void				save(::std::string);
			void				load(::std::string);
			void				construct(math::geo::polyhedron*);
			void				print(int sl);
			
			// draw data
			file_header			fh_;
			neb::vertex*			vertices_;
			GLushort*			indices_;
>>>>>>> d0a41ef6b864be74b7f06b355cf3c6c8c192ad68
	};
}

#endif


