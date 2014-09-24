
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/light/util/parent.hpp>

std::weak_ptr<neb::core::core::scene::base>		neb::core::core::light::util::parent::getScene() {
	auto shape = isShapeBase();
	assert(shape);
	
	auto parent = shape->parent_.lock();
	assert(parent);
	
	auto actor = parent->isActorBase();
	if(actor) return actor->getScene();

	abort();
	return std::weak_ptr<neb::core::core::scene::base>();
}

