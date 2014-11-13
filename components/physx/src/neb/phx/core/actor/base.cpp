#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>

<<<<<<< HEAD
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
	
=======
#include <neb/core/game/weapon/SimpleProjectile.hpp>

#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/base.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/util/log.hpp>

neb::phx::core::actor::base::base()
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
}
neb::phx::core::actor::base::~base() {
	LOG(lg, neb::phx::core::actor::sl, info) << __PRETTY_FUNCTION__;
}
void			neb::phx::core::actor::base::init(parent_t * const & p)
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
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
<<<<<<< HEAD
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
=======
/*std::shared_ptr<neb::phx::core::actor::util::parent>		neb::phx::core::actor::base::getPxParent() {
	auto parent(phx::core::actor::base::parent_.lock());
	assert(parent);
	return parent;
}*/
void			neb::phx::core::actor::base::hit() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;

	auto parent(getParent());

	physx::PxU32 w2 = simulation_.word2;

	if(w2 & phx::filter::filter::PROJECTILE)
	{
		LOG(lg, neb::phx::core::actor::sl, debug) << shared_from_this().get() << " is projectile, erase";
		parent->erase(_M_index);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	}

	if(flag_.any(neb::core::core::actor::util::flag::E::DESTRUCTIBLE)) {
		damage(0.6f);
	}
}
void			neb::phx::core::actor::base::damage(double h) {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;

	health_ -= h;
	if(health_ < 0) {
<<<<<<< HEAD
		get_parent()->erase(i_);
=======
		getParent()->erase(_M_index);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
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
<<<<<<< HEAD
std::weak_ptr<neb::phx::game::weapon::SimpleProjectile>			neb::phx::core::actor::base::createWeaponSimpleProjectile(
		std::shared_ptr<neb::gfx::window::base> window,
=======

typedef neb::game::weapon::SimpleProjectile Weapon;

std::weak_ptr<Weapon>			neb::phx::core::actor::base::createWeaponSimpleProjectile(
		std::shared_ptr<neb::core::input::source> src,
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
		double size,
		double damage,
		double velocity) {

	auto self(isPxActorBase());
<<<<<<< HEAD

	auto weap(sp::make_shared<neb::phx::game::weapon::SimpleProjectile>());

	weap->actor_ = self;
	weap->connect(window);
=======
	
	std::shared_ptr<Weapon> weap(new Weapon());

	//weap->actor_ = self;
	weap->setParent(this);

	weap->connect(src);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

	weap->velocity_ = velocity;
	weap->size_ = size;
	weap->damage_ = damage;

<<<<<<< HEAD
	neb::phx::game::weapon::util::parent::insert(weap);
=======
	neb::game::weapon::util::parent::insert(weap);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

	return weap;
}




