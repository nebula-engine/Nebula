#ifndef __GLUTPP_NETWORK_ACTOR_EVENT_H__
#define __GLUTPP_NETWORK_ACTOR_EVENT_H__

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
#include <gru/Message/Actor/Base.hpp>

namespace Neb {
	namespace Message {
		namespace Actor {
			/** @brief %Event */
			class Event: public Neb::Message::Actor::Base {
				public:
					virtual void		serializeDerived(boost::archive::binary_oarchive & ar, unsigned int const & version);
				public:
					glutpp::actor::addr				addr_;
					boost::shared_ptr<Neb::Event::Actor::Base>	event_;
			};
		}
	}
}

#endif



