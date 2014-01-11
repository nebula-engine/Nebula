#include <neb/physics.h>
#include <neb/actor/Rigid_Actor.h>
#include <neb/shape.h>


neb::actor::Rigid_Actor::Rigid_Actor(
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	neb::actor::Actor(scene, actor)
{

}
void neb::actor::Rigid_Actor::init(glutpp::actor::desc_s desc) {
	neb::actor::Actor::init(desc);
}
void	neb::actor::Rigid_Actor::step_remote(double) {

}
void	neb::actor::Rigid_Actor::setupFiltering()
{
	assert(px_actor_);

	physx::PxRigidActor* actor = (physx::PxRigidActor*)px_actor_;

	physx::PxFilterData coll_data;
	coll_data.word0 = raw_.filter_data_.simulation_.word0;
	coll_data.word1 = raw_.filter_data_.simulation_.word1;
	coll_data.word2 = raw_.filter_data_.simulation_.word2;
	coll_data.word3 = raw_.filter_data_.simulation_.word3;

	physx::PxFilterData sq_data;
	sq_data.word0 = raw_.filter_data_.scene_query_.word0;
	sq_data.word1 = raw_.filter_data_.scene_query_.word1;
	sq_data.word2 = raw_.filter_data_.scene_query_.word2;
	sq_data.word3 = raw_.filter_data_.scene_query_.word3;


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
glutpp::actor::desc_s neb::actor::Rigid_Actor::get_projectile() {
	abort();
	return glutpp::actor::desc_s();
}



