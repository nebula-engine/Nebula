#ifndef __NEBULA_SHAPE_H__
#define __NEBULA_SHAPE_H__

#include <tinyxml2.h>

//#include <math/vec3.hpp>

#include <Nebula/shape/shape.hpp>

#include <Nebula/shape/parent.hpp>

namespace Neb {
	namespace Shape {
		class Physical: public Neb::Shape::Base {
			public:
				Physical(Neb::Shape:Util::Parent_s);
				
				virtual void		init();
				void			create_physics();
				physx::PxGeometry*	to_geo();
				void			print_info();
			public:
				physx::PxShape*		px_shape_;
		};	
	}
}

#endif


