
#include <Nebula/Types.hh>
#include <Nebula/Physics.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/Shape/Physical.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

neb::Shape::Physical::Physical() {
}
neb::Shape::Physical::Physical(sp::shared_ptr<neb::Shape::Util::Parent> parent): neb::Shape::Base(parent) {
	//NEBULA_DEBUG_0_FUNCTION;
}
void neb::Shape::Physical::init() {
	//NEBULA_DEBUG_0_FUNCTION;
	
	neb::Shape::Physical::init();
	
	create_physics();
}
void neb::Shape::Physical::create_physics() {

	//NEBULA_DEBUG_0_FUNCTION;
	
	assert(!parent_.expired());
	
	auto parent = getParent();
	assert(parent);

	auto actor = parent->isActorBase();
	
	if(actor) {
		auto rigidactor = actor->isActorRigidActor();//std::dynamic_pointer_cast<neb::Actor::Rigid_Actor>(parent_.lock());

		if(rigidactor) {
			physx::PxRigidActor* px_rigid_actor = static_cast<physx::PxRigidActor*>(rigidactor->px_actor_);

			physx::PxMaterial* px_mat = neb::Physics::global()->px_physics_->createMaterial(1,1,1);

			px_shape_ = px_rigid_actor->createShape( *(to_geo()), *px_mat );
		}
	}
}







