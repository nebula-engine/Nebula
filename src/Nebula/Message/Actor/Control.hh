#ifndef NEBULA_MESSAGE_ACTOR_CONTROL_HPP
#define NEBULA_MESSAGE_ACTOR_CONTROL_HPP

#include <Nebula/Util/WrapperTyped.hh>

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


							Neb::WrapperTyped<Neb::Actor::Control::RigidBody::Base>		control_;
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

							Neb::WrapperTyped<Neb::Actor::Control::RigidBody::Base>		control_;
					};
				}
			}
		}
	}
}

#endif




