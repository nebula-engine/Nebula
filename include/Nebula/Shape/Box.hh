#ifndef NEBULA_SHAPE_BOX_HH
#define NEBULA_SHAPE_BOX_HH

#include <Nebula/Shape/Base.hh>

namespace neb {
	namespace Shape {
		class Box: public neb::Shape::Base {
			public:
				Box(sp::shared_ptr<neb::Shape::Util::Parent> parent);

				virtual void			createMesh();
		};
	}
}

#endif
