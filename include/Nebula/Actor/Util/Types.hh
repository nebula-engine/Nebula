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

		class Base;

		/** @brief %Actor */
		namespace actor {
			class Base;
			class local;
			class Remote;
		}
		/** @brief %rigidactor */
		namespace rigidactor {
			class Base;
			class local;
			class Remote;
		}

		/** @brief %RigidBody */
		namespace rigidbody {
			class Base;
			class local;
			class Remote;
		}

		/** @brief %RigidDynamic */
		namespace rigiddynamic {
			class Base;
			class local;
			class Remote;
		}

		/** @brief %RigidStatic */
		namespace RigidStatic {
			class Base;
			class local;
			class Remote;

		}

		class empty;


		/** @brief Utilities */
		namespace Util {
			class Parent;
		}

		/** @brief %Control */
		namespace Control {
			namespace rigidbody {
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
}}

#endif
