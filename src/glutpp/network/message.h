#ifndef __NEBULA_NETWORK_MESSAGE_H__
#define __NEBULA_NETWORK_MESSAGE_H__

#include <gal/network/vector.h>
#include <gal/network/serializeable.h>
#include <gal/network/serial.h>

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
					vec_addr_raw;

			typedef gal::network::serial_ext<
				glutpp::actor::desc,
				glutpp::actor::addr>
					ser_create;
		
			typedef gal::network::serial_ext<
				vec_addr_raw>
					ser_update;
			
			
			
			struct create: ser_create {
				void load(glutpp::actor::actor_s);
			};

			struct update: ser_update {
				typedef vec_addr_raw::tuple tuple;

				void load(glutpp::actor::actor_s);
			};
		}
		namespace scene {
			typedef gal::network::serial_ext<
				glutpp::scene::desc,
				glutpp::scene::addr>
					ser_create;
			
			struct create: ser_create {
				void load(glutpp::scene::scene_s);
			};
		}
	}
}

#endif

