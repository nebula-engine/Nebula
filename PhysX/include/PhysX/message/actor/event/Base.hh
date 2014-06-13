#ifndef __PX_NETWORK_ACTOR_EVENT_H__
#define __PX_NETWORK_ACTOR_EVENT_H__

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



namespace px { namespace message { namespace actor { namespace event {


	/** @brief %Base */
	class Base: virtual public neb::Message::actor::Base {
		public:
	};
	class IBase:
		virtual public neb::Message::actor::IBase,
		virtual public neb::Message::actor::Event::Base
	{
	};
	class OBase:
		virtual public neb::Message::actor::OBase,
		virtual public neb::Message::actor::Event::Base
	{
	};
	class Fire:
		virtual public neb::Message::actor::Event::Base
	{
	};
	class IFire:
		virtual public px::message::actor::event::IBase,
		virtual public px::message::actor::event::Fire
	{
		virtual void		process();

		virtual void		serialize(
				boost::archive::polymorphic_iarchive & ar,
				unsigned int const & version);
	};
	class OFire:
		virtual public px::message::actor::event::OBase,
		virtual public px::message::actor::event::Fire
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



