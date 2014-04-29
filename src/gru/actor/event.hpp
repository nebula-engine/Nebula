#ifndef __GLUTPP_ACTOR_EVENT_H__
#define __GLUTPP_ACTOR_EVENT_H__

#include <gru/config.hpp>
#include <gru/shape/desc.hpp>

namespace glutpp { namespace actor {
	class event {
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



