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

#include <Nebula/core/actor/Util/Types.hh>

#include <Nebula/message/Actor/Base.hh>



namespace neb {
	namespace message {
		namespace actor {
			namespace Event {
				/** @brief %Base */
				class base: virtual public neb::message::actor::base {
					public:
				};
				class IBase:
					virtual public neb::message::actor::IBase,
					virtual public neb::message::actor::Event::base
				{
				};
				class OBase:
					virtual public neb::message::actor::OBase,
					virtual public neb::message::actor::Event::base
				{
				};
			}
		}
	}
}

#endif



