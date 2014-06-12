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

#include <Galaxy-Standard/wrapper.hpp>

#include <Nebula/Actor/Util/Types.hh>

#include <Nebula/Message/Actor/Base.hh>



namespace neb {
	namespace Message {
		namespace Actor {
			namespace Event {
				/** @brief %Base */
				class Base: virtual public Neb::Message::Actor::Base {
					public:
				};
				class IBase:
					virtual public Neb::Message::Actor::IBase,
					virtual public Neb::Message::Actor::Event::Base
				{
				};
				class OBase:
					virtual public Neb::Message::Actor::OBase,
					virtual public Neb::Message::Actor::Event::Base
				{
				};
			}
		}
	}
}

#endif



