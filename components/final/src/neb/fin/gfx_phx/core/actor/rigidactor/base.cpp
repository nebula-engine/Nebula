#include <gal/log/log.hpp>

#include <neb/core/util/log.hpp>

#include <neb/fin/gfx_phx/core/shape/box.hpp>
#include <neb/fin/gfx_phx/core/actor/rigidactor/base.hpp>

neb::fin::gfx_phx::core::actor::rigidactor::base::base(std::shared_ptr<neb::fin::gfx_phx::core::actor::util::parent> parent):
	neb::core::core::actor::base(parent),
	neb::phx::core::actor::base(parent),
	neb::phx::core::actor::actor::base(parent),
	neb::phx::core::actor::rigidactor::base(parent),
	neb::gfx::core::actor::base(parent),
	neb::fin::gfx_phx::core::actor::base(parent)
{}
weak_ptr<neb::core::core::shape::base>	neb::fin::gfx_phx::core::actor::rigidactor::base::createShapeBoxUninitialized(
		glm::vec3 size) {
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;

	auto self(::std::dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::rigidactor::base>(shared_from_this()));
	
	auto shape = sp::make_shared<neb::fin::gfx_phx::core::shape::box>(self);

	neb::core::core::shape::util::parent::insert(shape);
	
	shape->s_ = size;
	
	return shape;
}
weak_ptr<neb::core::core::shape::base>				neb::fin::gfx_phx::core::actor::rigidactor::base::createShapeBox(neb::core::pose pose, glm::vec3 size) {
	LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;

	auto shape = createShapeBoxUninitialized(size).lock();
	
	shape->init();
	
	return shape;
}    

