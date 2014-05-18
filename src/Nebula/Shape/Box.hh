#ifndef NEBULA_SHAPE_BOX_HH
#define NEBULA_SHAPE_BOX_HH

namespace Neb {
	namespace Shape {
		class Box: public Neb::Shape::Physical {
			public:


				virtual physx::PxGeometry*	to_geo();
		};
	}
}

#endif
