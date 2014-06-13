#ifndef NEBULA_MESSAGE_ACTOR_CONTROL_HPP
#define NEBULA_MESSAGE_ACTOR_CONTROL_HPP

#include <Galaxy-Standard/wrapper.hpp>

#include <Nebula/Message/Actor/Base.hh>

#include <PhysX/core/actor/util/decl.hpp>

namespace px { namespace Message { namespace Actor { namespace Control {
	namespace RigidBody {
		/** @brief %Create. */
		class Create:
			virtual public neb::Message::actor::Base
		{
			gal::std::wrapper<px::core::actor::control::rigidbody::base>		control_;
		};
		/** @brief %Create. */
		class ICreate:
			virtual public neb::Message::actor::Base
		{
			public:
				/** @brief derived serialize. */
				virtual void					serializeDerived(
						boost::archive::polymorphic_iarchive & ar,
						unsigned int const & version);
		};
		/** @brief %Create. */
		class OCreate:
			virtual public neb::Message::actor::Base
		{
			public:
				/** @brief derived serialize. */
				virtual void					serializeDerived(
						boost::archive::polymorphic_oarchive & ar,
						unsigned int const & version);
		};
		/** @brief %Update. */
		class Update:
			virtual public neb::Message::actor::Base
		{
			public:
				virtual ~Update() = 0;
			public:
				gal::std::wrapper<px::core::actor::control::rigidbody::base>		control_;
		};
		/** @brief %Update. */
		class IUpdate:
			virtual public neb::Message::actor::IBase,
			virtual public neb::Message::actor::control::rigidbody::Update
		{
			public:
				virtual ~IUpdate();
				/** @brief derived serialize. */
				virtual void					serialize(
						boost::archive::polymorphic_iarchive & ar,
						unsigned int const & version);
		};
		/** @brief %Update. */
		class OUpdate:
			virtual public neb::Message::actor::OBase,
			virtual public neb::Message::actor::control::rigidbody::Update
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




