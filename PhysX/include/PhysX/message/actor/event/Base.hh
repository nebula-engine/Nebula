#ifndef __PX_NETWORK_ACTOR_EVENT_H__
#define __PX_NETWORK_ACTOR_EVENT_H__

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



namespace phx { namespace message { namespace actor { namespace event {


	/** @brief %Base */
	class base: virtual public neb::message::actor::base {
		public:
	};
	class IBase:
		virtual public neb::message::actor::IBase,
		virtual public phx::message::actor::event::base
	{
	};
	class OBase:
		virtual public neb::message::actor::OBase,
		virtual public phx::message::actor::event::base
	{
	};
	class Fire:
		virtual public phx::message::actor::event::base
	{
	};
	class IFire:
		virtual public phx::message::actor::event::IBase,
		virtual public phx::message::actor::event::Fire
	{
		virtual void		process();

		virtual void		serialize(
				boost::archive::polymorphic_iarchive & ar,
				unsigned int const & version);
	};
	class OFire:
		virtual public phx::message::actor::event::OBase,
		virtual public phx::message::actor::event::Fire
	{
		//virtual void		pre();
		//virtual void		post();

		virtual void		serialize(
				boost::archive::polymorphic_oarchive & ar,
				unsigned int const & version);
	};
}
}
}
}

#endif



