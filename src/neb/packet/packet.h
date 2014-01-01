#ifndef __NEBULA_PACKET_H__
#define __NEBULA_PACKET_H__

#include <math/vec3.h>
#include <math/transform.h>

#include <neb/scene_desc.h>
#include <neb/actor/desc.h>


namespace neb
{
	namespace packet
	{
		enum type
		{
			ACTOR_FORCE,
			SCENE
		};
		
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
				neb::scene_desc			scene_desc;
			};
		};
		
		
	}
}

#endif
