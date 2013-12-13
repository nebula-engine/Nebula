#ifndef __NEBULA_CONTENT_ACTOR_LIGHT_H__
#define __NEBULA_CONTENT_ACTOR_LIGHT_H__

#include <neb/actor/Base.h>

namespace neb
{
	namespace actor
	{
		class Light:
			public neb::actor::Base
		{
			public:
				virtual void	init();
				virtual void	add_force();
		};
	}
}


#endif








