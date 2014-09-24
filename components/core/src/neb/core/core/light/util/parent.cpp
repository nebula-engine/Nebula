
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/shape/base.hpp>
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


