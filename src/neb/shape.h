#ifndef __NEBULA_SHAPE_H__
#define __NEBULA_SHAPE_H__

#include <tinyxml2.h>

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
			box(tinyxml2::XMLElement*);

	};
	class sphere: public neb::shape
	{
		public:
			sphere(float);
			sphere(tinyxml2::XMLElement*);
			float	radius_;
	};
}

#endif


