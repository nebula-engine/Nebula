#include <Nebula/Types.hpp>
#include <Nebula/physics.hpp>
#include <Nebula/Scene/scene.hpp>
#include <Nebula/shape/shape.hpp>
#include <Nebula/shape/Physical.hpp>
#include <Nebula/Actor/Rigid_Actor.hpp>
#include <Nebula/shape/raw.hpp>

Neb::Shape::Physical::Physical(Neb::Shape::parent_w parent): Neb::Shape::shape(parent) {
	//NEBULA_DEBUG_0_FUNCTION;
}
void Neb::Shape::Physical::init(Neb::weak_ptr<Neb::Shape::desc> desc) {
	//NEBULA_DEBUG_0_FUNCTION;
	
	Neb::Shape::Physical::init(desc);
	
	create_physics();
}
void Neb::Shape::Physical::create_physics() {

	//NEBULA_DEBUG_0_FUNCTION;
	
	assert(!parent_.expired());
	
	auto parent = getParent();
	assert(parent);

	auto actor = parent->isActor();
	
	if(actor) {
		auto rigidactor = actor->isRigidActor();//std::dynamic_pointer_cast<Neb::Actor::Rigid_Actor>(parent_.lock());

		if(rigidactor) {
			physx::PxRigidActor* px_rigid_actor = static_cast<physx::PxRigidActor*>(rigidactor->px_actor_);

			physx::PxMaterial* px_mat = Neb::__physics.px_physics_->createMaterial(1,1,1);

			px_shape_ = px_rigid_actor->createShape( *(to_geo()), *px_mat );
		}
	}
}
physx::PxGeometry* Neb::Shape::Physical::to_geo()
{
	//NEBULA_DEBUG_0_FUNCTION;

	physx::PxGeometry* geo = NULL;
	
	physx::PxVec3 s = raw_->s_;
	
	switch(raw_->type_.val_) {
		case Neb::Shape::Type::BOX:
			geo = new physx::PxBoxGeometry(s * 0.5);
			break;
		case Neb::Shape::Type::SPHERE:
			geo = new physx::PxSphereGeometry(s.x);
			break;
		default:
			printf("unknown shape type\n");
			abort();
	}

	return geo;
}
void Neb::Shape::Physical::print_info() {

	physx::PxReal dynamic_friction;
	physx::PxReal static_friction;
	physx::PxReal restitution;


	if(px_shape_ != NULL) {
		physx::PxU32 num_shapes = px_shape_->getNbMaterials();

		physx::PxMaterial** materials = new physx::PxMaterial*[num_shapes];

		num_shapes = px_shape_->getMaterials(materials, num_shapes);

		for(physx::PxU32 i = 0; i < num_shapes; ++i) {
			dynamic_friction = materials[i]->getDynamicFriction();
			static_friction = materials[i]->getStaticFriction();
			restitution = materials[i]->getRestitution();

			printf("dynamic friction = %f\n", dynamic_friction);
			printf("static friction  = %f\n", static_friction);
			printf("restitution      = %f\n", restitution);
		}
	}
}







