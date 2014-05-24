
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/Actor/Control/RigidBody/Base.hh>

#include <Nebula/Message/Actor/Control.hh>

void			Neb::Message::Actor::Control::RigidBody::IUpdate::serialize(
		boost::archive::polymorphic_iarchive & ar,
		unsigned int const & version)
{
	Neb::Message::Actor::IBase::serialize(ar, version);
	ar >> control_;
	

	auto actor = std::dynamic_pointer_cast<Neb::Actor::Base>(Neb::Util::Shared::registry_.get(index_));

	auto rigidbody = actor->isActorRigidBody();

	assert(rigidbody);

	assert(rigidbody->control_);

	rigidbody->control_->operator=(*control_.ptr_);
}




