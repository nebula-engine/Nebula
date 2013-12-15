#ifndef __NEBULA_PACKET_H__
#define __NEBULA_PACKET_H__

#include <math/vec3.h>

namespace neb
{
	struct actor_force
	{
		int i_;
		float	f_[3];
		float	t_[3];
	};


	struct packet
	{
		enum
{
ACTOR_FORCE
};

		int type_;

		union
		{
			actor_force af;
		};
	};
}

#endif
