#ifndef NEBULA_CORE_LIGHT_COUNT
#define NEBULA_CORE_LIGHT_COUNT

namespace neb { namespace core { namespace light { namespace util {

	struct count {
		count(): point(0), spot(0), directional(0) {}
		int	point, spot, directional;
	};

}}}}

#endif
