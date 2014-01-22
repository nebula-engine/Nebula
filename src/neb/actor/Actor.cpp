#include <glutpp/renderable.h>
#include <glutpp/scene/scene.h>

#include <neb/simulation_callback.h>
#include <neb/shape.h>
#include <neb/scene/scene.h>
#include <glutpp/actor/desc.h>
#include <neb/actor/Actor.h>

neb::actor::Actor::Actor(glutpp::parent_s parent):
	neb::actor::Base(parent),
	px_actor_(NULL)
{
	NEBULA_DEBUG_0_FUNCTION;
}
void neb::actor::Actor::init(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;

	neb::actor::Base::init(desc);
}
void	neb::actor::Actor::set_pose(math::transform pose) {
	NEBULA_DEBUG_1_FUNCTION;

	neb::actor::Base::set_pose(pose);
}
int	neb::actor::Actor::fire() {
	NEBULA_DEBUG_1_FUNCTION;
	return neb::actor::Base::fire();
}
void neb::actor::Actor::step_local(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	neb::actor::Base::step_local(time);
}
void neb::actor::Actor::step_remote(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	neb::actor::Base::step_remote(time);
}
void neb::actor::Actor::release() {
	NEBULA_DEBUG_0_FUNCTION;
	
	neb::actor::Base::release();

	//assert(!scene_.expired());

	assert(px_actor_);
	px_actor_->release();
	px_actor_ = NULL;
}
glutpp::actor::desc_s get_projectile() {
	NEBULA_DEBUG_1_FUNCTION;
	abort();
	return glutpp::actor::desc_s();
}
void neb::actor::Actor::print_info() {

	physx::PxActorType::Enum type	= px_actor_->getType();
	//physx::PxBounds bounds	= px_actor_->getWorldBounds();
	short unsigned int flags	= px_actor_->getActorFlags();
	
	printf("PxActor\n");
	printf("type  = %X\n", type);
	printf("flags = %X\n", flags);
	

}

