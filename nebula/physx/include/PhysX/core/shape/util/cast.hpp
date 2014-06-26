#ifndef PHYSX_CORE_SHAPE_UTIL_CAST_HPP
#define PHYSX_CORE_SHAPE_UTIL_CAST_HPP

#include <PhysX/core/shape/util/decl.hpp>

namespace phx { namespace core { namespace shape { namespace util {


	class cast:
		virtual public neb::core::shape::util::cast
	{
		public:
			sp::shared_ptr<phx::core::shape::base>		isPxShapeBase();
	};


}}}}

#endif
