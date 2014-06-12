#ifndef __GLUTPP_SHAPE_EMPTY_H__
#define __GLUTPP_SHAPE_EMPTY_H__

#include <Nebula/Shape/Base.hh>

namespace neb {
	namespace Shape {
		class Empty: public Neb::Shape::Base {
			public:
				Empty(sp::shared_ptr<Neb::Shape::Util::Parent> parent): Neb::Shape::Base(parent) {}
				virtual void			createMesh() {}
				
				virtual void			draw_elements(sp::shared_ptr<Neb::Graphics::Context::Base> context, mat4 space) {}
		};
	}
}

#endif




