#ifndef __NEBULA_SHAPE_H__
#define __NEBULA_SHAPE_H__

#include <tinyxml2.h>

//#include <math/vec3.hpp>

#include <Nebula/Shape/Base.hh>

//#include <Nebula/Shape/parent.hh>

namespace Neb {
	namespace Shape {
		class Physical: public Neb::Shape::Base {
			public:
				Physical();
				Physical(Neb::Shape::Util::Parent_s);
				
				virtual void		init();
				void			create_physics();
				physx::PxGeometry*	to_geo();
			public:
				physx::PxShape*		px_shape_;
		};	
	}
}

#endif


