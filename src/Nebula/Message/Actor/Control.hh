#ifndef NEBULA_MESSAGE_ACTOR_CONTROL_HPP
#define NEBULA_MESSAGE_ACTOR_CONTROL_HPP

#include <Nebula/config.hpp>
#include <Nebula/Message/Actor/Base.hh>

namespace Neb {
	namespace Message {
		namespace Actor {
			namespace Control {
				namespace RigidBody {
					
					/** @brief %Create. */
					class Create: public Neb::Message::Actor::Base {
						public:
							/** @brief derived serialize. */
							virtual void					serializeDerived(
									boost::archive::binary_oarchive & ar,
									unsigned int const & version);
							/** @brief derived serialize. */
							virtual void					serializeDerived(
									boost::archive::binary_iarchive & ar,
									unsigned int const & version);


							Neb::Actor::Control::RigidBody::Raw		raw_;
					};
					/** @brief %Update. */
					class Update: public Neb::Message::Actor::Base {
						public:
							/** @brief derived serialize. */
							virtual void					serializeDerived(
									boost::archive::binary_oarchive & ar,
									unsigned int const & version);
							/** @brief derived serialize. */
							virtual void					serializeDerived(
									boost::archive::binary_iarchive & ar,
									unsigned int const & version);

							Neb::Actor::Control::RigidBody::Raw		raw_;
					};
				}
			}
		}
	}
}

#endif




