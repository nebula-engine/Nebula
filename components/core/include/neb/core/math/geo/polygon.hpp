#ifndef __MATH_GEO_POLYGON_H__
#define __MATH_GEO_POLYGON_H__

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>



namespace math {
	namespace geo {

		class vertex;

		struct triangle {
			triangle();
			triangle(vertex*, vertex*, vertex*);
			triangle&	operator=(triangle const &);
			vertex*		verts_[3];

			void	reset_normals();
		};
		class polygon {
			public:
				polygon();
				triangle*	getTriangles();
				unsigned int	getNbTriangles();
				void		setTriangles(triangle*, unsigned int);
			protected:
				triangle*	triangles_;
				unsigned int	nbTriangles_;
		};
	}
}

#endif


