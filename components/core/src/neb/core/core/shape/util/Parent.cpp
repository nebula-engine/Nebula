
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/shape/util/parent.hpp>

void		neb::core::core::shape::util::parent::callbackPose(neb::core::pose const & parent_gpose) {
	
	auto lambda_shape = [&]  (map_type::iterator<0> it) {
		auto shape = std::dynamic_pointer_cast<neb::core::core::shape::base>(it->ptr_);
		assert(shape);
		
		auto gpose = parent_gpose * shape->pose_;

		shape->callbackPose(gpose);
	};
	
	map_.for_each<0>(lambda_shape);
}


