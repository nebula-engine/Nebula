#ifndef __GLUTPP_NETWORK_MESSAGE_H__
#define __GLUTPP_NETWORK_MESSAGE_H__

#include <gal/network/vector.h>
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

			typedef std::shared_ptr<vec_addr_raw> vec_addr_raw_s;

			typedef gal::network::serial_ext<
				glutpp::actor::desc,
				glutpp::actor::addr>
					ser_create;

			typedef gal::network::serial_ext<vec_addr_raw> ser_update;
			
			typedef gal::network::serial_ext<
				glutpp::actor::addr,
				glutpp::actor::event>
					ser_event;


			struct create: ser_create {
				void			load(glutpp::actor::actor_s);

				glutpp::actor::addr_s	get_addr() { return std::get<1>(tup_); }
				glutpp::actor::desc_s	get_desc() { return std::get<0>(tup_); }
			};

			struct update: ser_update {
				//typedef vec_addr_raw::tuple tuple;

				void load(glutpp::actor::actor_s);
			};

			struct event: ser_event {
				
				glutpp::actor::addr_s	get_addr() { return std::get<0>(tup_); }
				glutpp::actor::event_s	get_event() { return std::get<1>(tup_); }
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



