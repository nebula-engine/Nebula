#ifndef __NEBULA_SHAPE_H__
#define __NEBULA_SHAPE_H__

#include <tinyxml2.h>

#include <math/vec3.h>

#include <glutpp/shape.h>

namespace neb
{
	class shape: public glutpp::shape
	{
		public:
			physx::PxGeometry*	to_geo();
			
			physx::PxShape*		px_shape_;
	};	
}

#endif


