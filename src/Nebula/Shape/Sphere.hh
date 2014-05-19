#ifndef NEBULA_SHAPE_SPHERE_HH
#define NEBULA_SHAPE_SPHERE_HH

#include <Nebula/Shape/Physical.hh>

namespace Neb {
	namespace Shape {
		class Sphere: public Neb::Shape::Physical {
			public:
				virtual void			createMesh();

				virtual physx::PxGeometry*	to_geo();
		};
	}
}

#endif
