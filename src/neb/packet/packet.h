#ifndef __NEBULA_PACKET_H__
#define __NEBULA_PACKET_H__

#include <math/vec3.h>

#include <neb/actor/desc.h>

namespace neb
{
	struct actor_force
	{
		int i_;
		float	f_[3];
		float	t_[3];
	};

	namespace packet
	{	
		struct packet
		{
			enum type
			{
				ACTOR_FORCE
			};

			int type_;

			union
			{
				actor_force		af;
				neb::actor::desc	desc_actor;
			};
		};
	}
}

#endif
