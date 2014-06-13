
#include <Nebula/Actor/RigidBody/Base.hh>

#include <PhysX/message/control/Control.hh>

void			neb::Message::Actor::Control::RigidBody::IUpdate::serialize(
		boost::archive::polymorphic_iarchive & ar,
		unsigned int const & version)
{
	neb::Message::Actor::IBase::serialize(ar, version);
	ar >> control_;
	

	auto actor = std::dynamic_pointer_cast<neb::Actor::Base>(gal::std::shared::registry_.get(index_));

	auto rigidbody = actor->isActorRigidBody();

	assert(rigidbody);

	assert(rigidbody->control_);

	rigidbody->control_->operator=(*control_.ptr_);
}




