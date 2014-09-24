#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>

#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/base.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/game/weapon/SimpleProjectile.hpp>
#include <neb/phx/util/log.hpp>

neb::phx::core::actor::base::base(std::shared_ptr<neb::phx::core::actor::util::parent> parent):
	neb::core::core::actor::base(parent),
	parent_(parent),
	health_(1.0)
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
}
/*phx::core::actor::base::~base() {
	LOG(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}*/
void			neb::phx::core::actor::base::init() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	
	neb::core::core::actor::base::init();
	
	create_physics();
	init_physics();
}
/*void			phx::core::actor::base::release() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	
	neb::core::core::actor::base::release();
}*/
void			neb::phx::core::actor::base::step(gal::etc::timestep const & ts) {
	neb::core::core::actor::base::step(ts);
}
std::shared_ptr<neb::phx::core::actor::util::parent>		neb::phx::core::actor::base::getPxParent() {
	auto parent(phx::core::actor::base::parent_.lock());
	assert(parent);
	return parent;
}
void			neb::phx::core::actor::base::hit() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;

	auto parent(parent_.lock()); assert(parent);

	physx::PxU32 w2 = simulation_.word2;

	if(w2 & phx::filter::filter::PROJECTILE) {
		LOG(lg, neb::phx::core::actor::sl, debug) << shared_from_this().get() << " is projectile, erase";
		parent->erase(i_);
	}

	if(flag_.any(neb::core::core::actor::util::flag::E::DESTRUCTIBLE)) {
		damage(0.6f);
	}
}
void			neb::phx::core::actor::base::damage(double h) {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;

	health_ -= h;
	if(health_ < 0) {
		get_parent()->erase(i_);
	}
}
/*int			phx::core::actor::base::key_fun(std::shared_ptr<neb::gfx::window::base> window, int key, int scancode, int action, int mods) {
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
std::weak_ptr<neb::phx::game::weapon::SimpleProjectile>			neb::phx::core::actor::base::createWeaponSimpleProjectile(
		std::shared_ptr<neb::gfx::window::base> window,
		double size,
		double damage,
		double velocity) {

	auto self(isPxActorBase());

	auto weap(sp::make_shared<neb::phx::game::weapon::SimpleProjectile>());

	weap->actor_ = self;
	weap->connect(window);

	weap->velocity_ = velocity;
	weap->size_ = size;
	weap->damage_ = damage;

	neb::phx::game::weapon::util::parent::insert(weap);

	return weap;
}




