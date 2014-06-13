#ifndef __NEBULA_SHAPE_H__
#define __NEBULA_SHAPE_H__

#include <tinyxml2.h>

//#include <math/vec3.hpp>

#include <Nebula/Shape/Base.hh>

//#include <Nebula/Shape/parent.hh>

namespace Neb {
	namespace Shape {
		class Physical: public neb::Shape::Base {
			public:
				Physical();
				Physical(sp::shared_ptr<neb::Shape::Util::Parent>);
				
				virtual void		init();
				void			create_physics();
				physx::PxGeometry*	to_geo();
			public:
				physx::PxShape*		px_shape_;
		};	
	}
}

#endif


