#ifndef __GLUTPP_NETWORK_ACTOR_EVENT_H__
#define __GLUTPP_NETWORK_ACTOR_EVENT_H__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

/*
#include <Nebula/config.hh> // gru/config.hpp.in
#include <Nebula/master.hh>
#include <Nebula/scene/desc.hh>
#include <Nebula/actor/desc.hh>
#include <Nebula/actor/addr.hh>
#include <Nebula/actor/event.hh>
#include <Nebula/actor/raw_factory.hh>
#include <Nebula/actor/actor.hh>
*/

#include <Nebula/Actor/Util/Types.hh>

#include <Nebula/Message/Actor/Base.hh>



namespace Neb {
	namespace Message {
		namespace Actor {
			/** @brief %Event */
			class Event: public Neb::Message::Actor::Base {
				public:
					virtual void		serializeDerived(
							boost::archive::polymorphic_oarchive & ar,
							unsigned int const & version);
					virtual void		serializeDerived(
							boost::archive::polymorphic_iarchive & ar,
							unsigned int const & version);
				public:
					Neb::WrapperTyped<Neb::Actor::Event::Base>	event_;
			};
		}
	}
}

#endif



