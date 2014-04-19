#ifndef __NEBULA_ACTOR_RAW__
#define __NEBULA_ACTOR_RAW__

#include <gal/network/serial.h>
#include <gal/util.h>

#include <glutpp/actor/raw.h>
#include <glutpp/config.h>

#include <neb/config.h>

template void gal::reset<neb::actor::raw>(neb::actor::raw_s&);

namespace neb {
	namespace actor {
		class raw: public gal::network::serial<neb::actor::raw, glutpp::actor::raw> {
			public:
				friend class neb::actor::raw_factory;
				friend void gal::reset<neb::actor::raw>(neb::actor::raw_s&);
		
				raw();

				virtual void		load(tinyxml2::XMLElement*);		
				virtual void		load(glutpp::actor::actor_s);
				
				float			health_;
				
		};
	}
}

#endif


