
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/shape/util/parent.hpp>

void		neb::core::core::shape::util::parent::callbackPose(neb::core::pose const & parent_gpose) {
	
<<<<<<< HEAD
	auto lambda_shape = [&]  (map_type::iterator<0> it) {
		auto shape = std::dynamic_pointer_cast<neb::core::core::shape::base>(it->ptr_);
		assert(shape);
		
=======
	auto lambda_shape = [&] (map_type::pointer p) {
		//auto shape = std::dynamic_pointer_cast<neb::core::core::shape::base>(p);
		//assert(shape);
		
		auto shape = std::static_pointer_cast<neb::core::core::shape::base>(p);

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
		auto gpose = parent_gpose * shape->pose_;

		shape->callbackPose(gpose);
	};
	
<<<<<<< HEAD
	map_.for_each<0>(lambda_shape);
=======
	map_.for_each(lambda_shape);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
}


