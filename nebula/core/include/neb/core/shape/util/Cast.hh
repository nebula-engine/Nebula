#ifndef NEBULA_SHAPE_UTIL_CAST_HH
#define NEBULA_SHAPE_UTIL_CAST_HH

#include <Galaxy-Standard/shared.hpp>

#include <neb/core/shape/util/Types.hh>

namespace neb { namespace core { namespace shape { namespace util {


			class cast:
				virtual public gal::std::shared
			{
				public:
					sp::shared_ptr<neb::core::shape::base>		isShapeBase();
			};


}}}}

#endif
