#ifndef __GLUTPP_ACTOR_EVENT_H__
#define __GLUTPP_ACTOR_EVENT_H__

#include <math/transform.hpp>

#include <galaxy/network/serial.hpp>
#include <galaxy/util.hpp>

#include <gru/config.hpp>
#include <gru/shape/desc.hpp>

namespace glutpp { namespace actor {
	class event: public gal::network::serial<event, gal::network::base> {
		public:
			struct type {
				enum e {
					NONE = 0x0,
					FIRE = 0x1,
				};
			};
			
			glutpp::actor::event::type::e		type_;

	};
}
}

#endif



