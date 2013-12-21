#ifndef __NEBULA_ACTOR_DESC_H__
#define __NEBULA_ACTOR_DESC_H__

#include <math/transform.h>

namespace neb
{
	namespace packet
	{
		struct vec3
		{
			float	x, y, z;
		};
		struct quat
		{
			vec3	v;
			float	w;
		};
		struct transform
		{
			math::transform		to_math();
			
			vec3	p;
			quat	q;
		};
	}



	class shape;
	namespace actor
	{
		enum type
		{
			NONE = 0,
			BASE,
			ACTOR,
			RIGID_ACTOR,
			RIGID_BODY,
			RIGID_DYNAMIC,
			RIGID_STATIC,
			CONTROLLER,
			LIGHT
		};
		struct desc
		{
			desc();
			type		type_;

			packet::transform	pose;
			packet::vec3		velocity;
			float			density;
			
			physx::PxU32	filter_group;
			physx::PxU32	filter_mask;

			neb::shape*	shape;
		};
	}
}

#endif
