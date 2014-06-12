#ifndef NEBULA_ACTOR_TYPES_HPP
#define NEBULA_ACTOR_TYPES_HPP

#include <memory>

namespace sp = ::std;

namespace neb {
	/** @brief %Actor */
	namespace Actor {
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

		class Base;

		/** @brief %Actor */
		namespace Actor {
			class Base;
			class Local;
			class Remote;
		}
		/** @brief %rigidactor */
		namespace RigidActor {
			class Base;
			class Local;
			class Remote;
		}

		/** @brief %RigidBody */
		namespace RigidBody {
			class Base;
			class Local;
			class Remote;
		}

		/** @brief %RigidDynamic */
		namespace RigidDynamic {
			class Base;
			class Local;
			class Remote;
		}

		/** @brief %RigidStatic */
		namespace RigidStatic {
			class Base;
			class Local;
			class Remote;

		}

		class empty;


		/** @brief Utilities */
		namespace Util {
			class Parent;
		}

		/** @brief %Control */
		namespace Control {
			namespace RigidBody {
				enum Type {
					NONE = 0,
					T0,
					T1,
				};

				//class Raw;
				//typedef boost::shared_ptr<raw>		Raw_s;

				class Base;
				class Manual;

			}
		}

		/** @brief %Event */
		namespace Event {
			class Base;
		}
	}
}

#endif
