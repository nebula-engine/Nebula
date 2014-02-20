#ifndef __NEB_PARENT_H__
#define __NEB_PARENT_H__

#include <neb/config.h>

namespace neb {
	class parent: public std::enable_shared_from_this<parent> {
		public:
			parent(neb::parent_s = neb::parent_s());
			virtual ~parent();
			
			neb::parent_s			get_parent();

			neb::actor::Base_s		is_actor();
			neb::shape::shape_s		is_shape();
	};
}                                               

#endif  

