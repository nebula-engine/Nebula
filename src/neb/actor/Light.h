#ifndef __NEBULA_CONTENT_ACTOR_LIGHT_H__
#define __NEBULA_CONTENT_ACTOR_LIGHT_H__

#include <glutpp/light.h>

#include <neb/actor/Base.h>

namespace neb
{
	namespace actor
	{
		class Light: public glutpp::light
		{
			public:
				virtual void	init();
				virtual void	add_force();
		};
	}
}


#endif








