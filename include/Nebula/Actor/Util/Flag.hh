#ifndef NEBULA_ACTOR_UTIL_FLAG_HH
#define NEBULA_ACTOR_UTIL_FLAG_HH

namespace neb { namespace core {
	namespace actor {
		namespace util {
			DEFINE_FLAG(Flag,
					((SHOULD_UPDATE)(1 << 1))
					((DESTRUCTIBLE)(1 << 2))
				   )
		}
	}
}}

#endif
