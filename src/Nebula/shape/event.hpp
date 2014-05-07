#ifndef __GLUTPP_ACTOR_EVENT_H__
#define __GLUTPP_ACTOR_EVENT_H__

#include <math/transform.h>
#include <math/raw/raw.h>

#include <gal/network/serial.h>
#include <gal/util.h>

#include <glutpp/config.h>
#include <glutpp/shape/desc.h>

namespace glutpp { namespace shape {
	class event: public gal::network::serial<event, gal::network::base> {
		public:
			struct type {
				enum e {
					NONE         = 0x0,
					SET_MATERIAL = 0x1,
				};
			};
			
			glutpp::shape::event::type::e		type_;
			
			int					i_;
	};
}
}

#endif



