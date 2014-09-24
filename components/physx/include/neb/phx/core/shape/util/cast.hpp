#ifndef PHYSX_CORE_SHAPE_UTIL_CAST_HPP
#define PHYSX_CORE_SHAPE_UTIL_CAST_HPP

#include <neb/phx/core/shape/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace shape { namespace util {
	class cast:
		virtual public neb::core::core::shape::util::cast
	{
		public:
			shared_ptr<neb::phx::core::shape::base>		isPxShapeBase();
	};
}}}}}

#endif
