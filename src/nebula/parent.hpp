#ifndef __NEB_PARENT_H__
#define __NEB_PARENT_H__


#include <gru/parent.hpp>

#include <nebula/config.hpp>

namespace neb {
	class parent: virtual public glutpp::parent {
		public:
			parent(neb::parent_s = neb::parent_s());
			virtual ~parent();
			
			neb::parent_s			getParent();
			
			neb::actor::Base_s		isActor();
			neb::actor::RigidActor_s	isRigidActor();
			neb::shape::shape_s		isShape();
	};
}

#endif  

