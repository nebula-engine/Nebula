
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/shape/base.hpp>
<<<<<<< HEAD
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

=======
#include <neb/core/core/light/base.hpp>
#include <neb/core/core/light/util/parent.hpp>

void							neb::core::core::light::util::parent::callbackPose(neb::core::pose const & parent_gpose) {
	
	auto lamb = [&] (map_type::pointer p) {
		//auto shape = std::dynamic_pointer_cast<neb::core::core::shape::base>(p);
		//assert(shape);
		
		auto light = std::static_pointer_cast<neb::core::core::light::base>(p);

		auto gpose = parent_gpose * light->pose_;

		light->callbackPose(gpose);
	};
	
	map_.for_each(lamb);
}


>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
