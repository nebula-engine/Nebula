#ifndef NEBULA_SHAPE_BOX_HH
#define NEBULA_SHAPE_BOX_HH

#include <Nebula/Shape/Base.hh>

namespace Neb {
	namespace Shape {
		class Box: public Neb::Shape::Base {
			public:
				Box(sp::shared_ptr<Neb::Shape::Util::Parent> parent);

				virtual void			createMesh();
		};
	}
}

#endif
