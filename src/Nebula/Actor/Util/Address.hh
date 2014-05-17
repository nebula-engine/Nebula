#ifndef __NEBULA_ACTOR_ADDRESS_HH
#define __NEBULA_ACTOR_ADDRESS_HH

//#include <math/transform.hpp>
//#include <math/raw/raw.hpp>

#include <deque>

#include <boost/serialization/deque.hpp>

#include <Nebula/Actor/Util/Types.hh>

#include <Nebula/Scene/Util/Address.hh>
//#include <Nebula/actor/actor.hh>

namespace Neb {
	namespace Actor {
		namespace Util {
			class Address {
				public:
					void					load_this(Neb::Actor::Base_s const &);
					void					load_parent(Neb::Actor::Base_s const &);
					
					template <class Archive> void		serialize(Archive & ar, unsigned int const & version) {
						ar & scene_;
						ar & vec_;
					}
					
					Neb::Scene::Util::Address		scene_;
					std::deque<int>				vec_;
					
					
			};
		}
	}
}

#endif




