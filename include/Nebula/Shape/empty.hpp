#ifndef __GLUTPP_SHAPE_EMPTY_H__
#define __GLUTPP_SHAPE_EMPTY_H__

#include <Nebula/Shape/Base.hh>

namespace Neb {
	namespace Shape {
		class Empty: public Neb::Shape::Base {
			public:
				Empty(sp::shared_ptr<Neb::Shape::Util::Parent> parent): Neb::Shape::Base(parent) {}
				virtual void		createMesh() {}
				
				virtual void		draw_elements(Neb::Graphics::Window::Base_s, mat4 space) {}
		};
	}
}

#endif




