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
		typedef gal::network::message_ext<
				glutpp::actor::addr_raw_vec
				> actor_update;
		
		typedef gal::network::message_ext<
				gal::network::vector<glutpp::actor::desc>,
				glutpp::scene::raw,
				glutpp::scene::addr
				> scene_create
				
		typedef gal::network::message_ext<
				glutpp::actor::addr_raw_vec
				> actor_create;
				
		
	}
}

#endif

