
#include <Nebula/Actor/Actor/PhysX.hpp>

void		Neb::Actor::Actor::PhysX::release() {
	NEBULA_ACTOR_BASE_FUNC;
	
	Neb::Actor::Base::release();

	//assert(!scene_.expired());

	assert(px_actor_);
	px_actor_->release();
	px_actor_ = NULL;
}


