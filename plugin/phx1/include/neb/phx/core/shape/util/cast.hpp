#ifndef PHYSX_CORE_SHAPE_UTIL_CAST_HPP
#define PHYSX_CORE_SHAPE_UTIL_CAST_HPP

#include <neb/fnd/core/shape/util/cast.hpp>

#include <neb/phx/core/shape/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace shape { namespace util {
	class cast:
		virtual public neb::fnd::core::shape::util::cast
	{
		public:
			std::shared_ptr<neb::phx::core::shape::base>		isPxShapeBase();
	};
}}}}}

#endif
