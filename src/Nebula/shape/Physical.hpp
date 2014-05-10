#ifndef __NEBULA_SHAPE_H__
#define __NEBULA_SHAPE_H__

#include <tinyxml2.h>

//#include <math/vec3.hpp>

#include <Nebula/shape/shape.hpp>

#include <Nebula/shape/parent.hpp>

namespace Neb {
	namespace Shape {
		class Physical: public Neb::Shape::shape {
			public:
				Physical(Neb::Shape::parent_w);

				virtual void		init(Neb::weak_ptr<Neb::Shape::desc>);
				void			create_physics();
				physx::PxGeometry*	to_geo();
				void			print_info();

				physx::PxShape*		px_shape_;
		};	
	}
}

#endif


