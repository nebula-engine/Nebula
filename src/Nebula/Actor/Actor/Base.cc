
#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Scene/Base.hh>

#include <Nebula/debug.hh>
#include <Nebula/simulation_callback.hh>
#include <Nebula/Shape/Base.hh>

#include <Nebula/Actor/Util/desc.hh>
#include <Nebula/Actor/Actor/Base.hh>

Neb::Actor::Actor::Base::Base() {
}
Neb::Actor::Actor::Base::Base(Neb::Actor::Util::Parent_s parent):
	Neb::Actor::Base(parent),
	px_actor_(NULL)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void Neb::Actor::Actor::Base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	Neb::Actor::Base::init();
}
void	Neb::Actor::Actor::Base::set_pose(physx::PxTransform pose) {
	NEBULA_ACTOR_BASE_FUNC;

	Neb::Actor::Base::setPose(pose);
}
int	Neb::Actor::Actor::Base::fire() {
	NEBULA_ACTOR_BASE_FUNC;
	return Neb::Actor::Base::fire();
}
void		Neb::Actor::Actor::Base::step(double dt) {
}


void		Neb::Actor::Actor::Base::release() {
	NEBULA_ACTOR_BASE_FUNC;
	
	Neb::Actor::Base::release();

	//assert(!scene_.expired());

	assert(px_actor_);
	px_actor_->release();
	px_actor_ = NULL;
}

