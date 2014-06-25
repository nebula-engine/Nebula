#ifndef PHYSX_MESSAGE_ACTOR_CONTROL_HPP
#define PHYSX_MESSAGE_ACTOR_CONTROL_HPP

#include <Galaxy-Standard/wrapper.hpp>

#include <neb/message/Actor/Base.hh>

#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace message { namespace actor { namespace control {

	namespace rigidbody {


		/** @brief %create. */
		class create:
			virtual public neb::message::actor::base
		{
			gal::std::wrapper<phx::core::actor::control::rigidbody::base>		control_;
		};
		/** @brief %create. */
		class icreate:
			virtual public neb::message::actor::base
		{
			public:
				/** @brief derived serialize. */
				virtual void					serializederived(
						boost::archive::polymorphic_iarchive & ar,
						unsigned int const & version);
		};
		/** @brief %create. */
		class ocreate:
			virtual public neb::message::actor::base
		{
			public:
				/** @brief derived serialize. */
				virtual void					serializeDerived(
						boost::archive::polymorphic_oarchive & ar,
						unsigned int const & version);
		};
		/** @brief %Update. */
		class update:
			virtual public neb::message::actor::base
		{
			public:
				virtual ~update() = 0;
			public:
				gal::std::wrapper<phx::core::actor::control::rigidbody::base>		control_;
		};
		/** @brief %update. */
		class iupdate:
			virtual public neb::message::actor::IBase,
			virtual public phx::message::actor::control::rigidbody::update
		{
			public:
				virtual ~iupdate();
				/** @brief derived serialize. */
				virtual void					serialize(
						boost::archive::polymorphic_iarchive & ar,
						unsigned int const & version);
		};
		/** @brief %update. */
		class oupdate:
			virtual public neb::message::actor::OBase,
			virtual public phx::message::actor::control::rigidbody::update
		{
			public:
				/** @brief derived serialize. */
				virtual void					serialize(
						boost::archive::polymorphic_oarchive & ar,
						unsigned int const & version);
		};
	}
}
}
}
}

#endif




