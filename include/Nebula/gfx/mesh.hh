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

#include <Nebula/math/geo/decl.hpp>

//#include <Nebula/config.hh>
#include <Nebula/gfx/material.hh>


namespace neb { namespace gfx {
	class mesh {
		public:
			mesh();
			~mesh();

			void				serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
			void				serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version);
			
			void				construct(math::geo::polyhedron*);
			void				print(int sl);
			

			/** @todo boost wont let me use shared ptr here! */
			::std::vector< math::geo::vertex >			vertices_;
			::std::vector<GLushort>						indices_;
			
	};
}}

#endif


