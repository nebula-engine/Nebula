#ifndef NEB_CORE_CORE_ACTOR_UTIL_FLAG_HH
#define NEB_CORE_CORE_ACTOR_UTIL_FLAG_HH

#include <gal/etc/flag.hpp>

namespace neb { namespace core { namespace core { namespace actor { namespace util {
	DEFINE_FLAG(flag,
			((SHOULD_UPDATE)(1 << 1))
			((DESTRUCTIBLE)(1 << 2))
		   )
}}}}}

#endif
