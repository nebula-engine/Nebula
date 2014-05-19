#include <Nebula/debug.hh>

#include <Nebula/Actor/Actor/Remote.hh>

void		Neb::Actor::Actor::Remote::step(double dt) {
	NEBULA_ACTOR_BASE_FUNC;

	Neb::Actor::Actor::Base::step(dt);
	Neb::Actor::Remote::step(dt);
}



