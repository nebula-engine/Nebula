#ifndef __NEBULA_ACTOR_ADDR_H__
#define __NEBULA_ACTOR_ADDR_H__

//#include <math/transform.hpp>
//#include <math/raw/raw.hpp>

#include <deque>

#include <boost/serialization/deque.hpp>

#include <gru/scene/addr.hpp>
//#include <gru/actor/actor.hpp>

namespace glutpp {
	namespace actor {
		//typedef gal::network::vector<int> vec_int;
		//typedef std::shared_ptr<vec_int> vec_int_s;



		class addr { //: public gal::network::serial_ext<vec_int, glutpp::scene::addr> {
			public:
				void	load_this(Neb::weak_ptr<glutpp::actor::actor> const &);
				void	load_parent(Neb::weak_ptr<glutpp::actor::actor> const &);
				
				template <class Archive> void		serialize(Archive & ar, unsigned int const & version) {
					ar & scene_;
					ar & vec_;
				}
				
				glutpp::scene::addr	scene_;
				std::deque<int>		vec_;


		};
	}
}

#endif








