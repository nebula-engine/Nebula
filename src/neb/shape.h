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
			shape(glutpp::actor::actor_s);
			
			virtual void		init(glutpp::shape::desc_s);
			void			create_physics();
			physx::PxGeometry*	to_geo();
			void			print_info();
			
			physx::PxShape*		px_shape_;
	};	
}

#endif


