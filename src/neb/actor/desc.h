#ifndef __NEBULA_ACTOR_DESC_H__
#define __NEBULA_ACTOR_DESC_H__

#include <math/transform.h>

namespace neb
{
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
			desc(neb::actor::type t = NONE);
			type		type_;
			math::transform pose_;
			neb::shape*	shape_;
		};
	}
}

#endif
