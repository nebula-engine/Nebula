#ifndef __NEBULA_SHAPE_H__
#define __NEBULA_SHAPE_H__

#include <tinyxml2.h>

#include <math/vec3.h>

#include <neb/packet/basic.h>

namespace neb
{
	class shape
	{
		public:
			enum
			{
				NONE = 0,
				BOX,
				SPHERE
			};

			int			box(math::vec3);
			int			box(tinyxml2::XMLElement*);
			
			int			sphere(float);
			int			sphere(tinyxml2::XMLElement*);

			physx::PxGeometry*	to_geo();

			int			type;
			neb::packet::vec3	s;
		};	
}

#endif


