#ifndef NEBULA_ACTOR_TYPES_HPP
#define NEBULA_ACTOR_TYPES_HPP

#include <memory>

namespace sp = ::std;

namespace neb { namespace core {
	/** @brief %Actor */
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

		// Core

		class base;

		/** @brief %actor */
		namespace actor {
			class base;
			class local;
			class remote;
		}
		/** @brief %rigidactor */
		namespace rigidactor {
			class base;
			class local;
			class remote;
		}

		/** @brief %rigidbody */
		namespace rigidbody {
			class base;
			class local;
			class remote;
		}

		/** @brief %rigiddynamic */
		namespace rigiddynamic {
			class base;
			class local;
			class remote;
		}

		/** @brief %rigidstatic */
		namespace rigidstatic {
			class base;
			class local;
			class remote;

		}

		class empty;


		/** @brief Utilities */
		namespace util {
			class parent;
		}


		/** @brief %Event */
		namespace Event {
			class base;
		}
	}
}}

#endif
