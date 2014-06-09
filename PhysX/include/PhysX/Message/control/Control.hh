#ifndef NEBULA_MESSAGE_ACTOR_CONTROL_HPP
#define NEBULA_MESSAGE_ACTOR_CONTROL_HPP

#include <Galaxy-Standard/wrapper.hpp>

#include <Nebula/Message/Actor/Base.hh>

namespace Neb {
	namespace Message {
		namespace Actor {
			namespace Control {
				namespace RigidBody {
					/** @brief %Create. */
					class Create:
						virtual public Neb::Message::Actor::Base
					{
						gal::std::wrapper<Neb::Actor::Control::RigidBody::Base>		control_;
					};
					/** @brief %Create. */
					class ICreate:
						virtual public Neb::Message::Actor::Base
					{
						public:
							/** @brief derived serialize. */
							virtual void					serializeDerived(
									boost::archive::polymorphic_iarchive & ar,
									unsigned int const & version);
					};
					/** @brief %Create. */
					class OCreate:
						virtual public Neb::Message::Actor::Base
					{
						public:
							/** @brief derived serialize. */
							virtual void					serializeDerived(
									boost::archive::polymorphic_oarchive & ar,
									unsigned int const & version);
					};
					/** @brief %Update. */
					class Update:
						virtual public Neb::Message::Actor::Base
					{
						public:
							virtual ~Update() = 0;
						public:
							gal::std::wrapper<Neb::Actor::Control::RigidBody::Base>		control_;
					};
					/** @brief %Update. */
					class IUpdate:
						virtual public Neb::Message::Actor::IBase,
						virtual public Neb::Message::Actor::Control::RigidBody::Update
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
						virtual public Neb::Message::Actor::OBase,
						virtual public Neb::Message::Actor::Control::RigidBody::Update
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




