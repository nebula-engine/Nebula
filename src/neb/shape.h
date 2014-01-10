#ifndef __NEBULA_SHAPE_H__
#define __NEBULA_SHAPE_H__

#include <tinyxml2.h>

#include <math/vec3.h>

#include <glutpp/shape/shape.h>

namespace neb
{
	class shape: public glutpp::shape::shape
	{
		public:
			shape(glutpp::actor::actor_shared);
			
			virtual void		init(glutpp::shape::desc_shared);
			void			create_physics();
			physx::PxGeometry*	to_geo();
			
			physx::PxShape*		px_shape_;
	};	
}

#endif


