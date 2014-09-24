#ifndef __MATH_GEO_POLYHEDRON_H__
#define __MATH_GEO_POLYHEDRON_H__

//#include <PxPhysicsAPI.h>

#include <neb/core/math/geo/polygon.hpp>
#include <neb/core/math/geo/quad.hpp>

namespace math {
	namespace geo {
		struct polyhedron {
				enum
				{
					PER_FACE_NORMAL
				};

				int		triangle_count();
				vector< std::shared_ptr<tri> >		triangles();

				vector< std::shared_ptr<polygon> >		polygons_;

				unsigned int	flag_;
		};
		class polyhedron_convex: public polyhedron
		{
		};
		class sphere: public polyhedron_convex
		{
			public:
				sphere(float,int,int);
		};
		class wedge: public polyhedron_convex
		{

		};
		class tetrahedron: public polyhedron_convex
		{

		};
		class cuboid: public polyhedron_convex
		{
			public:
				cuboid(float,float,float);
		};
	}
}

#endif


