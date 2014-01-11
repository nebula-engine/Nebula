#ifndef __NEBULA_ACTOR_ADDR_H__
#define __NEBULA_ACTOR_ADDR_H__

#include <math/transform.h>
#include <math/raw/raw.h>

#include <glutpp/scene/desc.h>
#include <glutpp/actor/actor_base.h>

namespace glutpp
{
	namespace actor
	{
		class addr
		{
			public:
				void			load(glutpp::actor::actor_shared);


				size_t			size();
				void			write(gal::network::message_shared);
				void			read(gal::network::message_shared);
			
				
				//glutpp::actor::actor_shared	actor_;
				
				glutpp::scene::addr		scene_addr_;
				
				gal::network::vector<int>	vec_;
		};
	}
}

#endif








