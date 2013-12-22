#ifndef __NEBULA_PACKET_H__
#define __NEBULA_PACKET_H__

#include <math/vec3.h>
#include <math/transform.h>

#include <neb/actor/desc.h>

namespace neb
{
	namespace packet
	{
		struct actor_force
		{
			int i_;
			float	f_[3];
			float	t_[3];
		};

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
				neb::packet::vec3	desc_actor;
				neb::packet::quat	q;
				neb::shape		s;
			};
		};
	}
}

#endif
