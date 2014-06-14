
#include <Nebula/debug.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

neb::core::actor::RigidActor::Base::Base() {
}
neb::core::actor::RigidActor::Base::Base(sp::shared_ptr<neb::core::actor::Util::Parent> parent): neb::core::actor::actor::Base(parent) {
}
void		neb::core::actor::RigidActor::Base::init() {

}
void		neb::core::actor::RigidActor::Base::step(neb::core::TimeStep const & ts) {
	neb::core::actor::actor::Base::step(ts);
}
void		neb::core::actor::RigidActor::Base::setupFiltering() {
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




