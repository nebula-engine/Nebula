#ifndef NEBULA_SHAPE_UTIL_CAST_HH
#define NEBULA_SHAPE_UTIL_CAST_HH

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/Shape/Util/Types.hh>

namespace Neb {
	namespace shape {
		namespace util {
			class Cast:
				virtual public gal::std::shared
			{
				public:
					sp::shared_ptr<neb::core::shape::base>		isShapeBase();
			};
		}
	}
}

#endif
