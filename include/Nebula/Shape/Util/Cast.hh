#ifndef NEBULA_SHAPE_UTIL_CAST_HH
#define NEBULA_SHAPE_UTIL_CAST_HH

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/Shape/Util/Types.hh>

namespace neb {
	namespace Shape {
		namespace Util {
			class Cast:
				virtual public gal::std::shared
			{
				public:
					neb::Shape::Base_s		isShapeBase();
			};
		}
	}
}

#endif
