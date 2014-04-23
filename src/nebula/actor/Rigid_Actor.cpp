
#include <nebula/physics.hpp>
#include <nebula/actor/Rigid_Actor.hpp>
#include <nebula/shape.hpp>


neb::Actor::RigidActor::RigidActor(glutpp::actor::parent_s parent):
	neb::Actor::Actor(parent)
{

}
void neb::Actor::RigidActor::init(glutpp::actor::desc_s desc) {
	neb::Actor::Actor::init(desc);
}
void	neb::Actor::RigidActor::step_local(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	neb::Actor::Actor::step_local(time);
}
void	neb::Actor::RigidActor::step_remote(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	neb::Actor::Actor::step_remote(time);
}
void	neb::Actor::RigidActor::setupFiltering()
{
	assert(px_actor_);

	physx::PxRigidActor* actor = (physx::PxRigidActor*)px_actor_;

	physx::PxFilterData coll_data;
	coll_data.word0 = raw_->filter_data_.simulation_.word0;
	coll_data.word1 = raw_->filter_data_.simulation_.word1;
	coll_data.word2 = raw_->filter_data_.simulation_.word2;
	coll_data.word3 = raw_->filter_data_.simulation_.word3;

	physx::PxFilterData sq_data;
	sq_data.word0 = raw_->filter_data_.scene_query_.word0;
	sq_data.word1 = raw_->filter_data_.scene_query_.word1;
	sq_data.word2 = raw_->filter_data_.scene_query_.word2;
	sq_data.word3 = raw_->filter_data_.scene_query_.word3;


	const physx::PxU32 numShapes = actor->getNbShapes();

	physx::PxShape** shapes = new physx::PxShape*[numShapes];

	actor->getShapes(shapes, numShapes);

	for(physx::PxU32 i = 0; i < numShapes; i++)
	{
		physx::PxShape* shape = shapes[i];
		shape->setSimulationFilterData(coll_data);
		shape->setQueryFilterData(sq_data);
	}

	delete[] shapes;
}
glutpp::actor::desc_s neb::Actor::RigidActor::get_projectile() {
	abort();
	return glutpp::actor::desc_s();
}
void neb::Actor::RigidActor::print_info() {

	neb::Actor::Actor::print_info();
	
	auto pxra = px_actor_->isRigidActor();
	
	physx::PxShape* pxshape;
	
	physx::PxReal dynamic_friction;
	physx::PxReal static_friction;
	physx::PxReal restitution;
	
	physx::PxU32 num_shapes = pxra->getNbShapes();
	
	physx::PxShape** shapes = new physx::PxShape*[num_shapes];
	
	num_shapes = pxra->getShapes(shapes, num_shapes);
	
	for(physx::PxU32 i = 0; i < num_shapes; ++i) {
		pxshape = shapes[i];
		
		physx::PxU32 num_materials = pxshape->getNbMaterials();

		physx::PxMaterial** materials = new physx::PxMaterial*[num_materials];

		num_materials = pxshape->getMaterials(materials, num_shapes);

		for(physx::PxU32 i = 0; i < num_materials; ++i) {
			dynamic_friction = materials[i]->getDynamicFriction();
			static_friction = materials[i]->getStaticFriction();
			restitution = materials[i]->getRestitution();

			printf("dynamic friction = %f\n", dynamic_friction);
			printf("static friction  = %f\n", static_friction);
			printf("restitution      = %f\n", restitution);
		}

	}
}




