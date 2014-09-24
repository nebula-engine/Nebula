#ifndef __GLUTPP_NETWORK_ACTOR_EVENT_H__
#define __GLUTPP_NETWORK_ACTOR_EVENT_H__

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

/*
#include <neb/config.hh> // gru/config.hpp.in
#include <neb/master.hh>
#include <neb/scene/desc.hh>
#include <neb/actor/desc.hh>
#include <neb/actor/addr.hh>
#include <neb/actor/event.hh>
#include <neb/actor/raw_factory.hh>
#include <neb/actor/actor.hh>
*/

#include <Galaxy-Standard/wrapper.hpp>

#include <neb/core/actor/Util/Types.hh>

#include <neb/message/Actor/Base.hh>



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



