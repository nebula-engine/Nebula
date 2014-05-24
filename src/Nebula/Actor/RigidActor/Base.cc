
#include <Nebula/debug.hh>
#include <Nebula/physics.hh>
#include <Nebula/Actor/RigidActor/Base.hh>
#include <Nebula/Shape/Physical.hh>

Neb::Actor::RigidActor::Base::Base() {
}
Neb::Actor::RigidActor::Base::Base(Neb::Actor::Util::Parent_s parent): Neb::Actor::Actor::Base(parent) {
}
void		Neb::Actor::RigidActor::Base::init() {

}
void		Neb::Actor::RigidActor::Base::step(double const & time, double const & dt) {
	//NEBULA_ACTOR_BASE_FUNC;
}
void		Neb::Actor::RigidActor::Base::setupFiltering() {
	assert(px_actor_);

	physx::PxRigidActor* actor = (physx::PxRigidActor*)px_actor_;

	physx::PxFilterData coll_data;
	coll_data.word0 = simulation_.word0;
	coll_data.word1 = simulation_.word1;
	coll_data.word2 = simulation_.word2;
	coll_data.word3 = simulation_.word3;

	physx::PxFilterData sq_data;
	sq_data.word0 = scene_query_.word0;
	sq_data.word1 = scene_query_.word1;
	sq_data.word2 = scene_query_.word2;
	sq_data.word3 = scene_query_.word3;


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




