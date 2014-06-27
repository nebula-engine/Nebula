
#include <neb/final/gfx_phx/core/actor/rigidactor/base.hpp>

::std::weak_ptr<neb::core::shape::base>				phx::core::actor::rigidactor::base::createShapeBoxUninitialized() {

	auto self(isPxActorRigidActorBase());

	auto shape = sp::make_shared<phx::core::shape::box>(self);
	
	neb::core::shape::util::parent::insert(shape);
	
	return shape;
}
::std::weak_ptr<neb::core::shape::base>				phx::core::actor::base::createShapeBox(glm::vec3 size) {

	auto self(isActorRigidActor());

	auto shape = sp::make_shared<neb::final::gfx_core::core::shape::box>(self);

	neb::core::shape::util::parent::insert(shape);

	return shape;
}    

