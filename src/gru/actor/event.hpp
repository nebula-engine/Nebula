#ifndef __GLUTPP_ACTOR_EVENT_H__
#define __GLUTPP_ACTOR_EVENT_H__

#include <gru/config.hpp>
#include <gru/shape/desc.hpp>

namespace Neb {
	namespace Event {
		namespace Actor {
			class Base {
				public:
					template<class Archive> void		serialize(Archive & ar, unsigned int const & version) {
						ar & hash_code_;
						serialize_derived(ar, version);
					}
					

					static int hash_code_;
			};
			class Fire {
				public:
					template<class Archive> void		serialize(Archive & ar, unsigned int const & version) {
						Base::serialize(ar, version);
					}
			};
		}
	}
}

#endif



