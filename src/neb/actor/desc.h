#ifndef __NEBULA_ACTOR_DESC_H__
#define __NEBULA_ACTOR_DESC_H__

#include <math/transform.h>

#include <neb/shape.h>
#include <neb/packet/basic.h>

namespace neb
{
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
			int			load(tinyxml2::XMLElement*);

			neb::actor::type	type;

			packet::transform	pose;
			packet::vec3		velocity;
			float			density;
			
			physx::PxU32		filter_group;
			physx::PxU32		filter_mask;

			neb::shape		shape;
		};
	}
}

#endif


