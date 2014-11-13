#ifndef NEBULA_SHAPE_UTIL_CAST_HH
#define NEBULA_SHAPE_UTIL_CAST_HH

#include <gal/itf/shared.hpp>

#include <neb/core/core/shape/util/decl.hpp>

using namespace std;

namespace neb { namespace core { namespace core { namespace shape { namespace util {
	class cast:
		virtual public gal::itf::shared
	{
		public:
			shared_ptr<neb::core::core::shape::base>		isShapeBase();
	};
}}}}}

#endif
