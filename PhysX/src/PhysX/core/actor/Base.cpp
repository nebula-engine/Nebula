

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

neb::Actor::Base::Base() {
}
neb::Actor::Base::Base(sp::shared_ptr<neb::Actor::Util::Parent> parent): parent_(parent) {
	NEBULA_ACTOR_BASE_FUNC;
}
neb::Actor::Base::~Base() {
	NEBULA_ACTOR_BASE_FUNC;
}
	void neb::Actor::Base::init() {
		NEBULA_ACTOR_BASE_FUNC;



		create_physics();
		create_children(desc);
		create_shapes(desc);
		init_physics();
	}
	int	neb::Actor::Base::fire() {
		NEBULA_ACTOR_BASE_FUNC;

		printf("%s\n", __PRETTY_FUNCTION__);

		getScene()->fire(isActorBase());

		return 1;
	}
	void neb::Actor::Base::hit() {

		physx::PxU32 w2 = simulation_.word2;

		if(w2 & neb::Filter::Filter::PROJECTILE) {
			parent_->release(i_);
			//set(neb::Actor::Base::flag::e::SHOULD_RELEASE);
		}

		if(flag_.any(neb::Actor::Util::Flag::E::DESTRUCTIBLE)) {
			damage(0.1);
		}
	}
	void neb::Actor::Base::damage(float h) {
		health_ -= h;
		if(health_ < 0) {
			parent_->release(i_);
		}
	}
	int neb::Actor::Base::key_fun(int key, int scancode, int action, int mods) {
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




