#ifndef NEBULA_SHAPE_BOX_HH
#define NEBULA_SHAPE_BOX_HH

#include <Nebula/Shape/Physical.hh>

namespace Neb {
	namespace Shape {
		class Box: public neb::Shape::Physical {
			public:
				virtual void			createMesh();
				
				virtual physx::PxGeometry*	to_geo();
		};
	}
}

#endif
