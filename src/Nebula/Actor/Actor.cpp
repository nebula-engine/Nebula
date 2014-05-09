
#include <Nebula/renderable.hpp>
#include <Nebula/Scene/scene.hpp>

#include <Nebula/debug.hpp>
#include <Nebula/simulation_callback.hpp>
#include <Nebula/shape/shape.hpp>
#include <Nebula/Scene/scene.hpp>

#include <Nebula/Actor/Util/desc.hpp>
#include <Nebula/Actor/Actor.hpp>

Neb::Actor::Actor::Actor(Neb::Actor::parent_w parent):
	Neb::Actor::Base(parent),
	px_actor_(NULL)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void Neb::Actor::Actor::init(Neb::Actor::desc_w desc) {
	NEBULA_ACTOR_BASE_FUNC;

	Neb::Actor::Base::init(desc);
}
void	Neb::Actor::Actor::set_pose(physx::PxTransform pose) {
	NEBULA_ACTOR_BASE_FUNC;

	Neb::Actor::Base::setPose(pose);
}
int	Neb::Actor::Actor::fire() {
	NEBULA_ACTOR_BASE_FUNC;
	return Neb::Actor::Base::fire();
}
void Neb::Actor::Actor::step_local(double time) {
	NEBULA_ACTOR_BASE_FUNC;
	Neb::Actor::Base::step_local(time);
}
void Neb::Actor::Actor::step_remote(double time) {
	NEBULA_ACTOR_BASE_FUNC;
	Neb::Actor::Base::step_remote(time);
}
void				Neb::Actor::Actor::release() {
	NEBULA_ACTOR_BASE_FUNC;
	
	Neb::Actor::Base::release();

	//assert(!scene_.expired());

	assert(px_actor_);
	px_actor_->release();
	px_actor_ = NULL;
}
void Neb::Actor::Actor::print_info() {

	physx::PxActorType::Enum type	= px_actor_->getType();
	//physx::PxBounds bounds	= px_actor_->getWorldBounds();
	short unsigned int flags	= px_actor_->getActorFlags();
	
	printf("PxActor\n");
	printf("type  = %X\n", type);
	printf("flags = %X\n", flags);
	

}

