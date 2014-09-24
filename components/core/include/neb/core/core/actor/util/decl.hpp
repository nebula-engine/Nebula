#ifndef NEBULA_ACTOR_TYPES_HPP
#define NEBULA_ACTOR_TYPES_HPP

#include <memory>

namespace neb { namespace core { namespace core {
	/** @brief %actor */
	namespace actor {
		struct mode_create {
			enum e {
				NOW,
				DEFERRED,
			};
		};
		struct mode_update {
			enum e {
				NONE   = 0x0,
				LOCAL  = 0x1,
				REMOTE = 0x2,
			};
		};

		class base;

		/** @brief util */
		namespace util {
			class parent;
		}
	}
}}}

#endif
