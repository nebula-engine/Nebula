#ifndef __NEBULA_ACTOR_RAW__
#define __NEBULA_ACTOR_RAW__

namespace neb {
	namespace actor {
		class raw: public gal::network::serial<raw, glutpp::actor::raw> {

		};
	}
}

#endif
