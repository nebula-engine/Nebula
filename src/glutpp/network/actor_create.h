#ifndef __NEBULA_NETWORK_ACTOR_CREATE_H__
#define __NEBULA_NETWORK_ACTOR_CREATE_H__

#include <gal/network/message_ext.h>

#include <glutpp/config.h>

namespace glutpp
{
	namespace network
	{
		class actor_create:
			public gal::network::message_ext<glutpp::actor::raw, glutpp::actor::addr>
		{
			public:
				actor_create(int);
		};
	}
}

#endif



