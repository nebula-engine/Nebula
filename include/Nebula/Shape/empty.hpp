#ifndef __GLUTPP_SHAPE_EMPTY_H__
#define __GLUTPP_SHAPE_EMPTY_H__

#include <Nebula/Shape/Base.hh>

namespace neb {
	namespace Shape {
		class Empty: public neb::Shape::Base {
			public:
				Empty(sp::shared_ptr<neb::Shape::Util::Parent> parent): neb::Shape::Base(parent) {}
				virtual void			createMesh() {}
				
				virtual void			draw_elements(sp::shared_ptr<neb::gfx::Context::Base> context, mat4 space) {}
		};
	}
}

#endif




