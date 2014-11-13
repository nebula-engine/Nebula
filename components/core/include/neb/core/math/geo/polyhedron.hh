#ifndef __MATH_GEO_POLYHEDRON_H__
#define __MATH_GEO_POLYHEDRON_H__

//#include <PxPhysicsAPI.h>

<<<<<<< HEAD
#include <neb/core/math/geo/polygon.hpp>
#include <neb/core/math/geo/quad.hpp>

namespace math {
	namespace geo {
=======
//#include <neb/core/math/geo/polygon.hpp>
//#include <neb/core/math/geo/quad.hpp>

namespace math {
	namespace geo {

		class triangle;
		class polygon;

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
		struct polyhedron {
				enum
				{
					PER_FACE_NORMAL
				};

<<<<<<< HEAD
				int		triangle_count();
				vector< std::shared_ptr<tri> >		triangles();

				vector< std::shared_ptr<polygon> >		polygons_;
=======
				polyhedron();

				unsigned int	getNbTriangles();
				triangle*	getTriangles();

				polygon*	polygons_;
				unsigned int	nbPolys_;
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

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


