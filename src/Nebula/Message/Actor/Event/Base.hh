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

#include <Nebula/Util/WrapperTyped.hh>

#include <Nebula/Actor/Util/Types.hh>

#include <Nebula/Message/Actor/Base.hh>



namespace Neb {
	namespace Message {
		namespace Actor {
			namespace Event {
				/** @brief %Base */
				class Base: virtual public Neb::Message::Actor::Base {
					public:
						
						/*virtual void		serialize(
								boost::archive::polymorphic_iarchive & ar,
								unsigned int const & version);*/
						virtual void		pre();
						virtual void		post();
				};
				class OBase:
					virtual public Neb::Message::Actor::OBase,
					virtual public Neb::Message::Actor::Event::Base
				{

				};
				class Fire:
					virtual public Neb::Message::Actor::Event::Base
				{
				};
				class OFire:
					virtual public Neb::Message::Actor::Event::OBase,
					virtual public Neb::Message::Actor::Event::Fire
				{
					virtual void		pre();
					virtual void		post();

					virtual void		serialize(
							boost::archive::polymorphic_oarchive & ar,
							unsigned int const & version);
				};
			}
		}
	}
}

#endif



