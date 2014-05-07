#ifndef __GLUTPP_NETWORK_MESSAGE_H__
#define __GLUTPP_NETWORK_MESSAGE_H__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <gru/config.hpp> // gru/config.hpp.in
#include <gru/master.hpp>
#include <gru/scene/desc.hpp>
#include <gru/actor/desc.hpp>
#include <gru/actor/addr.hpp>
#include <gru/actor/event.hpp>
#include <gru/actor/raw_factory.hpp>
#include <gru/actor/actor.hpp>

namespace glutpp {
	namespace network {
		namespace scene {
			struct create {
				void load(Neb::weak_ptr<glutpp::scene::scene> scene);
				
				template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
					ar & addr_;
					ar & desc_;
				}

				glutpp::scene::addr	addr_;
				glutpp::scene::desc	desc_;
			};
		}
	}
}

#endif



