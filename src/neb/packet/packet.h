#ifndef __NEBULA_PACKET_H__
#define __NEBULA_PACKET_H__

#include <math/vec3.h>
#include <math/transform.h>

//#include <neb/scene/desc.h>
#include <glutpp/actor/desc.h>


namespace neb
{
	namespace packet
	{
		
		struct actor_force
		{
			int		i_;
			float		f_[3];
			float		t_[3];
		};
		
		struct packet
		{
			int	type;
			union
			{
				neb::packet::actor_force	actor_force;
			};
		};
	}
}

#endif
