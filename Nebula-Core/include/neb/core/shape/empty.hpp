#ifndef __GLUTPP_SHAPE_EMPTY_H__
#define __GLUTPP_SHAPE_EMPTY_H__

#include <neb/core/shape/Base.hh>

namespace neb { namespace core {
	namespace shape {
		class empty: public neb::core::shape::base {
			public:
				empty(sp::shared_ptr<neb::core::shape::util::parent> parent): neb::core::shape::base(parent) {}
				
		};
	}
}}

#endif




