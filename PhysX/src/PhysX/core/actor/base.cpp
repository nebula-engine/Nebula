#include <Galaxy-Log/log.hpp>

#include <Nebula/debug.hh>

//#include <Nebula/util/Typed.hh>

/*#include <Nebula/util/decl.hpp>
#include <Nebula/config.hh> // Nebula/config.hpp.in
#include <Nebula/timer/Actor/Base.hpp>
#include <Nebula/app/Base.hh>
#include <Nebula/core/scene/Base.hh>
#include <Nebula/gfx/window/util/signals.hpp>

#include <Nebula/core/actor/Base.hh>
#include <Nebula/core/actor/RigidActor/Base.hh>
#include <Nebula/core/actor/RigidBody/Base.hh>
#include <Nebula/core/actor/Empty/Empty.hpp>
#include <Nebula/core/actor/Util/Types.hh>

#include <Nebula/Filter.hh>
#include <Nebula/gfx/window/Base.hh>
*/

#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/base.hpp>
#include <PhysX/core/scene/base.hpp>
#include <PhysX/game/weapon/SimpleProjectile.hpp>

phx::core::actor::base::base(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	parent_(parent),
	health_(1.0)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
}
/*phx::core::actor::base::~base() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}*/
void			phx::core::actor::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::base::init();
	
	create_physics();
	init_physics();
}
/*void			phx::core::actor::base::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::base::release();
}*/
void			phx::core::actor::base::step(gal::std::timestep const & ts) {
	neb::core::actor::base::step(ts);
}
sp::shared_ptr<phx::core::actor::util::parent>		phx::core::actor::base::getPxParent() {
	auto parent(phx::core::actor::base::parent_.lock());
	assert(parent);
	return parent;
}
void			phx::core::actor::base::hit() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	auto parent(parent_.lock()); assert(parent);

	physx::PxU32 w2 = simulation_.word2;

	if(w2 & phx::filter::filter::PROJECTILE) {
		parent->erase(i_);
	}

	if(flag_.any(neb::core::actor::util::flag::E::DESTRUCTIBLE)) {
		damage(0.6f);
	}
}
void			phx::core::actor::base::damage(float h) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
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
sp::weak_ptr<phx::game::weapon::SimpleProjectile>			phx::core::actor::base::createWeaponSimpleProjectile(
		sp::shared_ptr<neb::gfx::window::base> window,
		real size,
		real damage,
		real velocity) {
	
	auto self(isPxActorBase());
	
	auto weap(sp::make_shared<phx::game::weapon::SimpleProjectile>());
	
	weap->actor_ = self;
	weap->connect(window);
	
	weap->velocity_ = velocity;
	weap->size_ = size;
	weap->damage_ = damage;
	
	phx::game::weapon::util::parent::insert(weap);

	return weap;
}




