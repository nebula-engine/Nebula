#include <math/free.h>

//#include <glutpp/types.h>

#include <neb/config.h>
#include <neb/physics.h>
#include <neb/scene/scene.h>
#include <neb/shape.h>

neb::shape::shape(glutpp::actor::actor_s actor):
	glutpp::shape::shape(actor)
{
	NEBULA_DEBUG_0_FUNCTION;
}
void neb::shape::init(glutpp::shape::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;
	
	glutpp::shape::shape::init(desc);
	
	create_physics();
}
void neb::shape::create_physics() {

	NEBULA_DEBUG_0_FUNCTION;
	
	assert(!actor_.expired());
	
	auto actor = std::dynamic_pointer_cast<neb::actor::Rigid_Actor>(actor_.lock());
	
	if(actor)
	{
		physx::PxRigidActor* px_rigid_actor = static_cast<physx::PxRigidActor*>(actor->px_actor_);

		physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);
	
		px_shape_ = px_rigid_actor->createShape( *(to_geo()), *px_mat );
	}
}
physx::PxGeometry* neb::shape::to_geo()
{
	NEBULA_DEBUG_0_FUNCTION;

	physx::PxGeometry* geo = NULL;

	math::vec3 s = raw_.s_;

	switch(raw_.type_)
	{
		case glutpp::shape::type::BOX:
			geo = new physx::PxBoxGeometry(s/2.0);
			break;
		case glutpp::shape::type::SPHERE:
			geo = new physx::PxSphereGeometry(s.x);
			break;
		default:
			printf("unknown shape type\n");
			abort();
	}

	return geo;
}
void neb::shape::print_info() {
	
	physx::PxReal dynamic_friction;
	physx::PxReal static_friction;
	physx::PxReal restitution;
	
	
	if(px_shape_ != NULL)
	{
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







