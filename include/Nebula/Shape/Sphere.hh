#ifndef NEBULA_SHAPE_SPHERE_HH
#define NEBULA_SHAPE_SPHERE_HH

#include <Nebula/Shape/Base.hh>

namespace neb {
	namespace Shape {
		class Sphere: public Neb::Shape::Base {
			public:
				virtual void			createMesh();
		};
	}
}

#endif
