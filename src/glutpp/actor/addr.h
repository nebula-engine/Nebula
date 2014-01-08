#ifndef __NEBULA_ACTOR_ADDR_H__
#define __NEBULA_ACTOR_ADDR_H__

#include <math/transform.h>
#include <math/raw/raw.h>

#include <glutpp/actor/actor_base.h>

namespace glutpp
{
	namespace actor
	{
		class addr
		{
			public:
				void			write(gal::network::message_shared);
				void			read(gal::network::message_shared);
				size_t			size();
				
				
				
				glutpp::actor::actor_weak	actor_;
				std::vector<int>		vec_;
		};
	}
}

#endif








