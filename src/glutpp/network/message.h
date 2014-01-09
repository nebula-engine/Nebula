#ifndef __NEBULA_NETWORK_ACTOR_UPDATE_H__
#define __NEBULA_NETWORK_ACTOR_UPDATE_H__

#include <gal/network/vector.h>
#include <gal/network/serializeable.h>
#include <gal/network/message_ext.h>

#include <glutpp/config.h>
#include <glutpp/scene/desc.h>

namespace glutpp
{
	namespace network
	{
		namespace actor {
			typedef gal::network::vector<glutpp::actor::addr, glutpp::actor::raw> addr_raw_vec;
			
			typedef gal::network::message_ext<
				glutpp::actor::addr,
				glutpp::actor::raw> actor_create;
			
			typedef gal::network::message_ext<addr_raw_vec> actor_update;
		}
		namespace scene {
			typedef gal::network::message_ext<
				gal::network::vector<glutpp::actor::desc>,
				glutpp::scene::raw,
				glutpp::scene::addr> scene_create;
		}
	}
}

#endif

