#ifndef __NEBULA_NETWORK_MESSAGE_H__
#define __NEBULA_NETWORK_MESSAGE_H__

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
			typedef gal::network::vector_ext<
				glutpp::actor::raw,
				glutpp::actor::addr>
					addr_raw_vec;

			typedef gal::network::message_ext<
				glutpp::actor::desc,
				glutpp::actor::addr>
					me_create;

			typedef gal::network::message_ext<addr_raw_vec> me_update;

			struct create: me_create {
				void load(glutpp::actor::actor_shared);
			};

			struct update: me_update {
				typedef addr_raw_vec::tup tup;

				void load(glutpp::actor::actor_shared);
			};
		}
		namespace scene {
			typedef gal::network::message_ext<
				glutpp::scene::desc,
				glutpp::scene::addr>
					me_create;

			struct create: me_create {
				void load(glutpp::scene::scene_shared);
			};
		}
	}
}

#endif

