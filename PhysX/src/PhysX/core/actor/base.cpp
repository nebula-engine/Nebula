#include <Galaxy-Log/log.hpp>

#include <Nebula/debug.hh>

//#include <Nebula/Util/Typed.hh>

/*#include <Nebula/Types.hh>
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
*/

#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/base.hpp>
#include <PhysX/core/scene/base.hpp>

phx::core::actor::base::base(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	parent_(parent)
{
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
}
/*phx::core::actor::base::~base() {
	NEBULA_ACTOR_BASE_FUNC;
}*/
void			phx::core::actor::base::init() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::base::init();
	
	create_physics();
	init_physics();
}
void			phx::core::actor::base::release() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::base::release();
}
void			phx::core::actor::base::step(neb::core::TimeStep const & ts) {
	neb::core::actor::base::step(ts);
}
sp::shared_ptr<phx::core::actor::util::parent>		phx::core::actor::base::getPxParent() {
	auto parent(phx::core::actor::base::parent_.lock());
	assert(parent);
	return parent;
}
int			phx::core::actor::base::fire() {

	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	auto parent(parent_.lock());
	assert(parent);

	parent->getScene()->fire(isPxActorBase());

	return 1;
}
void			phx::core::actor::base::hit() {

	auto parent(parent_.lock()); assert(parent);

	physx::PxU32 w2 = simulation_.word2;

	if(w2 & neb::Filter::Filter::PROJECTILE) {
		parent->erase(i_);
	}

	if(flag_.any(neb::core::actor::util::Flag::E::DESTRUCTIBLE)) {
		damage(0.1f);
	}
}
void			phx::core::actor::base::damage(float h) {
	
	health_ -= h;
	if(health_ < 0) {
		get_parent()->erase(i_);
	}
}
/*int			phx::core::actor::base::key_fun(sp::shared_ptr<neb::gfx::window::base> window, int key, int scancode, int action, int mods) {
	switch(action) {
		case GLFW_PRESS:
			switch(key) {
				case GLFW_KEY_SPACE:
					fire();
					return 1;
			}
	}

	return 0;
}*/




