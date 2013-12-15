#ifndef __NEBULA_SHAPE_H__
#define __NEBULA_SHAPE_H__

#include <tinyxml/tinyxml.h>

#include <math/vec3.h>

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
			int			type_;
			math::vec3		s_;
			physx::PxGeometry*	geo_;
	};
	class box: public neb::shape
	{
		public:
			box(math::vec3);
			box(TiXmlElement*);

	};
	class sphere: public neb::shape
	{
		public:
			sphere(float);
			sphere(TiXmlElement*);
			float	radius_;
	};
}

#endif


