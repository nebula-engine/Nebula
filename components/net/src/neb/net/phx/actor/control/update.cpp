
#include <Galaxy-Standard/registry.hpp>

#include <PhysX/core/actor/rigidbody/base.hpp>
#include <PhysX/core/actor/control/rigidbody/base.hpp>
#include <PhysX/message/actor/control/rigidbody/update.hpp>

void			phx::message::actor::control::rigidbody::iupdate::serialize(
		boost::archive::polymorphic_iarchive & ar,
		unsigned int const & version)
{
	neb::message::actor::IBase::serialize(ar, version);
	ar >> control_;
	

	auto actor = std::dynamic_pointer_cast<phx::core::actor::base>(gal::itf::shared::registry_.get(index_));
	assert(actor);

	auto rigidbody = actor->isPxActorRigidBodyBase();

	assert(rigidbody);

	assert(rigidbody->control_);

	rigidbody->control_->operator=(*control_.ptr_);
}




