
#include <neb/fin/gfx_phx/core/actor/rigidstatic/base.hpp>
#include <neb/fin/gfx_phx/core/actor/rigiddynamic/base.hpp>
#include <neb/fin/gfx_phx/core/scene/base.hpp>

::std::weak_ptr<neb::core::actor::base>			neb::fin::gfx_phx::core::scene::base::createActorRigidStaticUninitialized() {

	auto self(::std::dynamic_pointer_cast<neb::fin::gfx_phx::core::scene::base>(shared_from_this()));

	auto actor(sp::make_shared<neb::fin::gfx_phx::core::actor::rigidstatic::base>(self));

	neb::core::actor::util::parent::insert(actor);

	actor->simulation_.word0 = phx::filter::filter::type::STATIC;
	actor->simulation_.word1 = phx::filter::filter::RIGID_AGAINST;
	actor->simulation_.word2 = phx::filter::filter::type::STATIC;
	actor->simulation_.word3 = phx::filter::filter::type::PROJECTILE;

	return actor;
}
::std::weak_ptr<neb::core::actor::base>			neb::fin::gfx_phx::core::scene::base::createActorRigidDynamicUninitialized() {

	auto self(::std::dynamic_pointer_cast<neb::fin::gfx_phx::core::scene::base>(shared_from_this()));

	auto actor = sp::make_shared<neb::fin::gfx_phx::core::actor::rigiddynamic::base>(self);

	neb::core::actor::util::parent::insert(actor);

	actor->simulation_.word0 = phx::filter::filter::type::DYNAMIC;
	actor->simulation_.word1 = phx::filter::filter::RIGID_AGAINST;
	actor->simulation_.word2 = phx::filter::filter::type::DYNAMIC;
	actor->simulation_.word3 = phx::filter::filter::type::PROJECTILE;

	return actor;

}

