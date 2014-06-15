
#include <Nebula/Actor/RigidBody/Base.hh>

#include <PhysX/message/actor/control/rigidbody/update.hpp>

void			phx::message::actor::Control::RigidBody::IUpdate::serialize(
		boost::archive::polymorphic_iarchive & ar,
		unsigned int const & version)
{
	neb::message::actor::IBase::serialize(ar, version);
	ar >> control_;
	

	auto actor = std::dynamic_pointer_cast<neb::core::actor::base>(gal::std::shared::registry_.get(index_));

	auto rigidbody = actor->isActorRigidBody();

	assert(rigidbody);

	assert(rigidbody->control_);

	rigidbody->control_->operator=(*control_.ptr_);
}




