#ifndef __NEBULA_ACTOR_ADDR_H__
#define __NEBULA_ACTOR_ADDR_H__

//#include <math/transform.hpp>
//#include <math/raw/raw.hpp>

#include <deque>

#include <boost/serialization/deque.hpp>

#include <Nebula/Scene/addr.hpp>
//#include <Nebula/actor/actor.hpp>

namespace Neb {
	namespace Actor {
		//typedef gal::network::vector<int> vec_int;
		//typedef std::shared_ptr<vec_int> vec_int_s;



		class addr {
			public:
				void					load_this(Neb::weak_ptr<Neb::Actor::Base> const &);
				void					load_parent(Neb::weak_ptr<Neb::Actor::Base> const &);
				
				template <class Archive> void		serialize(Archive & ar, unsigned int const & version) {
					ar & scene_;
					ar & vec_;
				}
				
				Neb::Scene::addr			scene_;
				std::deque<int>				vec_;


		};
	}
}

#endif








