#ifndef NEBULA_SHAPE_UTIL_CAST_HH
#define NEBULA_SHAPE_UTIL_CAST_HH

#include <Nebula/Util/Shared.hh>

#include <Nebula/Shape/Util/Types.hh>

namespace Neb {
	namespace Shape {
		namespace Util {
			class Cast:
				virtual public Neb::Util::Shared
			{
				public:
					Neb::Shape::Base_s		isShapeBase();
			};
		}
	}
}

#endif
