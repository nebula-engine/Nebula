
#include <Nebula/debug.hpp>
#include <Nebula/physics.hpp>
#include <Nebula/Actor/Rigid_Actor.hpp>
#include <Nebula/shape/Physical.hpp>


Neb::Actor::RigidActor::RigidActor(Neb::weak_ptr<Neb::Actor::parent> parent): Neb::Actor::Actor(parent) {}

void		Neb::Actor::RigidActor::init(Neb::weak_ptr<Neb::Actor::desc> desc) {
	Neb::Actor::Actor::init(desc);
}
void		Neb::Actor::RigidActor::step_local(double time) {
	NEBULA_ACTOR_BASE_FUNC;
	Neb::Actor::Actor::step_local(time);
}
void	Neb::Actor::RigidActor::step_remote(double time) {
	NEBULA_ACTOR_BASE_FUNC;
	Neb::Actor::Actor::step_remote(time);
}
void	Neb::Actor::RigidActor::setupFiltering()
{
	assert(px_actor_);

	physx::PxRigidActor* actor = (physx::PxRigidActor*)px_actor_;

	physx::PxFilterData coll_data;
	coll_data.word0 = raw_.simulation_.word0;
	coll_data.word1 = raw_.simulation_.word1;
	coll_data.word2 = raw_.simulation_.word2;
	coll_data.word3 = raw_.simulation_.word3;

	physx::PxFilterData sq_data;
	sq_data.word0 = raw_.scene_query_.word0;
	sq_data.word1 = raw_.scene_query_.word1;
	sq_data.word2 = raw_.scene_query_.word2;
	sq_data.word3 = raw_.scene_query_.word3;


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
void Neb::Actor::RigidActor::print_info() {

	Neb::Actor::Actor::print_info();
	
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




