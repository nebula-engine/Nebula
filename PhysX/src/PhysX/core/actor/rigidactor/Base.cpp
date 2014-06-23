#include <Galaxy-Log/log.hpp>

#include <PhysX/util/convert.hpp>
#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/rigidactor/base.hpp>

#include <PhysX/core/shape/box.hpp>

//neb::core::actor::rigidactor::base::base() {
//}
phx::core::actor::rigidactor::base::base(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	phx::core::actor::base(parent),
	phx::core::actor::actor::base(parent)
{
}
void		phx::core::actor::rigidactor::base::init() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::rigidactor::base::init();
	phx::core::actor::actor::base::init();
}
void		phx::core::actor::rigidactor::base::release() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::rigidactor::base::release();
	phx::core::actor::actor::base::release();

}
void		phx::core::actor::rigidactor::base::step(gal::std::timestep const & ts) {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::rigidactor::base::step(ts);
	phx::core::actor::actor::base::step(ts);
}
void		phx::core::actor::rigidactor::base::setupFiltering() {
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
void								phx::core::actor::rigidactor::base::setGlobalPosition(vec3 p) {
	/** @todo if is nested actor, then this is wrong... */
	pose_.pos_ = vec4(p,1);
	
	assert(px_actor_);
	auto px_rigidactor = px_actor_->isRigidActor();
	assert(px_rigidactor);
	px_rigidactor->setGlobalPose(physx::PxTransform(
				phx::util::convert(p),
				phx::util::convert(pose_.rot_)
				));
}
sp::weak_ptr<neb::core::shape::box>				phx::core::actor::rigidactor::base::createShapeBoxUninitialized() {

	auto self(isPxActorRigidActorBase());

	auto shape = sp::make_shared<phx::core::shape::box>(self);
	
	neb::core::shape::util::parent::insert(shape);
	
	return shape;
}




