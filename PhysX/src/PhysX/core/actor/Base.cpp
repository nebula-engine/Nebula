

#include <Nebula/debug.hh>

//#include <Nebula/Util/Typed.hh>

#include <Nebula/Types.hh>
#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/timer/Actor/Base.hpp>
#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Signals.hh>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/RigidActor/Base.hh>
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/Actor/Empty/Empty.hpp>
#include <Nebula/Actor/Util/Types.hh>

#include <Nebula/Filter.hh>
#include <Nebula/Graphics/Window/Base.hh>

#include <PhysX/core/actor/base.hpp>

phx::core::actor::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
/*phx::core::actor::base::~base() {
	NEBULA_ACTOR_BASE_FUNC;
}*/
void			phx::core::actor::base::init() {
	NEBULA_ACTOR_BASE_FUNC;


	create_physics();
	create_children(desc);
	create_shapes(desc);
	init_physics();
}
int			phx::core::actor::base::fire() {
	NEBULA_ACTOR_BASE_FUNC;

	printf("%s\n", __PRETTY_FUNCTION__);

	getScene()->fire(isActorBase());

	return 1;
}
void			phx::core::actor::base::hit() {

	physx::PxU32 w2 = simulation_.word2;

	if(w2 & neb::Filter::Filter::PROJECTILE) {
		parent_->release(i_);
		//set(neb::core::actor::base::flag::e::SHOULD_RELEASE);
	}

	if(flag_.any(neb::core::actor::util::Flag::E::DESTRUCTIBLE)) {
		damage(0.1);
	}
}
void			phx::core::actor::base::damage(float h) {
	health_ -= h;
	if(health_ < 0) {
		parent_->release(i_);
	}
}
int			phx::core::actor::base::key_fun(int key, int scancode, int action, int mods) {
	switch(action) {
		case GLFW_PRESS:
			switch(key) {
				case GLFW_KEY_SPACE:
					fire();
					return 1;
			}
	}

	return 0;
}




