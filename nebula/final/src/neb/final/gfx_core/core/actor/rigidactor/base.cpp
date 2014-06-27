
#include <neb/final/gfx_phx/core/shape/box.hpp>
#include <neb/final/gfx_phx/core/actor/rigidactor/base.hpp>

::std::weak_ptr<neb::core::shape::base>				neb::fin::gfx_phx::core::actor::rigidactor::base::createShapeBoxUninitialized(glm::vec3 size) {

	auto self(::std::dynamic_pointer_cast<neb::fin::gfx_phx::core::actor::rigidactor::base>(shared_from_this()));
	
	auto shape = sp::make_shared<neb::fin::gfx_phx::core::shape::box>(self);

	neb::core::shape::util::parent::insert(shape);
	
	shape->s_ = size;
	
	return shape;
}
::std::weak_ptr<neb::core::shape::base>				neb::fin::gfx_phx::core::actor::rigidactor::base::createShapeBox(glm::vec3 size) {

	auto shape = createShapeBoxUninitialized(size).lock();
	
	shape->init();
	
	return shape;
}    

