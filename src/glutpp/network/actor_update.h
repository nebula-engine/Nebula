#ifndef __NEBULA_NETWORK_ACTOR_UPDATE_H__
#define __NEBULA_NETWORK_ACTOR_UPDATE_H__

#include <gal/network/vector.h>
#include <gal/network/serializeable.h>

#include <glutpp/config.h>
#include <glutpp/scene/desc.h>

namespace glutpp
{
	namespace network
	{
		class actor_update:
			public gal::network::message_ext<gal::network::vector<glutpp::actor::raw>,glutpp::scene::id>
		{
			public:	
				
		};
	}
}

#endif

