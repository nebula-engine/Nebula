#ifndef NEBULA_SHAPE_SPHERE_HH
#define NEBULA_SHAPE_SPHERE_HH

namespace Neb {
	namespace Shape {
		class Sphere: public Neb::Shape::Physical {
			public:


				virtual physx::PxGeometry*	to_geo();
		};
	}
}

#endif
