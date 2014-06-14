#ifndef PHYSX_MESSAGE_ACTOR_CONTROL_HPP
#define PHYSX_MESSAGE_ACTOR_CONTROL_HPP

#include <Galaxy-Standard/wrapper.hpp>

#include <Nebula/Message/Actor/Base.hh>

#include <PhysX/core/actor/util/decl.hpp>

namespace px { namespace message { namespace actor { namespace Control {

	namespace rigidbody {

		/** @brief %Create. */
		class create:
			virtual public neb::message::actor::Base
		{
			gal::std::wrapper<px::core::actor::control::rigidbody::base>		control_;
		};
		/** @brief %Create. */
		class icreate:
			virtual public neb::message::actor::Base
		{
			public:
				/** @brief derived serialize. */
				virtual void					serialize(
						boost::archive::polymorphic_iarchive & ar,
						unsigned int const & version);
		};
		/** @brief %Create. */
		class ocreate:
			virtual public neb::message::actor::Base
		{
			public:
				/** @brief derived serialize. */
				virtual void					serialize(
						boost::archive::polymorphic_oarchive & ar,
						unsigned int const & version);
		};



	}
}}}}

#endif




