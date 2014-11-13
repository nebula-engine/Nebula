#ifndef NEBULA_ACTOR_TYPES_HPP
#define NEBULA_ACTOR_TYPES_HPP

#include <memory>

namespace neb { namespace core { namespace core {
<<<<<<< HEAD
	/** @brief %actor */
	namespace actor {
=======

	/** @brief %actor */
	namespace actor {

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
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

<<<<<<< HEAD
		class base;
=======
		namespace rigidbody {
			struct desc;
		}
		namespace rigiddynamic {
			struct desc;
		}

		class __base;
		class base;
		class desc;
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

		/** @brief util */
		namespace util {
			class parent;
		}
	}
<<<<<<< HEAD
=======

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
}}}

#endif
