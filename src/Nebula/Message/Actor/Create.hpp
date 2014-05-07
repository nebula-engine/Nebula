#ifndef __GLUTPP_NETWORK_ACTOR_CREATE_H__
#define __GLUTPP_NETWORK_ACTOR_CREATE_H__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <gru/config.hpp>
#include <gru/master.hpp>
#include <gru/scene/desc.hpp>
#include <gru/actor/desc.hpp>
#include <gru/actor/addr.hpp>
#include <gru/actor/event.hpp>
#include <gru/actor/raw_factory.hpp>
#include <gru/actor/actor.hpp>

namespace glutpp {
	namespace network {
		namespace actor {
			struct create {
				void				load(Neb::unique_ptr<glutpp::actor::actor> actor);

				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & addr_;
					ar & desc_;
				}
				
				glutpp::actor::addr	addr_; //() { return std::get<0>(ser_create::tup_); }
				glutpp::actor::desc	desc_; //() { return std::get<1>(tup_); }
			};
		}
	}
}





#endif


