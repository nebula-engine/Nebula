#ifndef __NEBULA_ACTOR_ADDRESS_HH
#define __NEBULA_ACTOR_ADDRESS_HH

//#include <math/transform.hpp>
//#include <math/raw/raw.hpp>

#include <deque>

#include <boost/serialization/deque.hpp>

#include <Nebula/Scene/addr.hpp>
//#include <Nebula/actor/actor.hpp>

namespace Neb {
	namespace Actor {
		namespace Util {
			class Address {
				public:
					void					load_this(Neb::weak_ptr<Neb::Actor::Base> const &);
					void					load_parent(Neb::weak_ptr<Neb::Actor::Base> const &);

					template <class Archive> void		serialize(Archive & ar, unsigned int const & version) {
						ar & scene_;
						ar & vec_;
					}

					Neb::Scene::Address			scene_;
					std::deque<int>				vec_;


			};
		}
	}
}

#endif








