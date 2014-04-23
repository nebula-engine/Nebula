#ifndef __NEBULA_ACTOR_RAW__
#define __NEBULA_ACTOR_RAW__

#include <galaxy/network/serial.hpp>
#include <galaxy/util.hpp>

#include <gru/actor/raw.hpp>
#include <gru/config.hpp>

#include <nebula/config.hpp>

template void gal::reset<neb::Actor::raw>(neb::Actor::raw_s&);

namespace neb {
	namespace Actor {
		class raw: public gal::network::serial<neb::Actor::raw, glutpp::actor::raw> {
			public:
				friend class neb::Actor::raw_factory;
				friend void gal::reset<neb::Actor::raw>(neb::Actor::raw_s&);
		
				raw();

				virtual void		load(tinyxml2::XMLElement*);		
				virtual void		load(glutpp::actor::actor_s);
				
				float			health_;
				
		};
	}
}

#endif


