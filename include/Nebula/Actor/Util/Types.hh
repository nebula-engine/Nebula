#ifndef NEBULA_ACTOR_TYPES_HPP
#define NEBULA_ACTOR_TYPES_HPP

#include <memory>

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

			typedef std::shared_ptr<Base>		Base_s;
			typedef std::weak_ptr<Base>		Base_w;
			typedef std::unique_ptr<Base>		Base_u;
		}

		namespace RigidActor {
			class Base;
			class Local;
			class Remote;

			typedef std::shared_ptr<Base>	Base_s;
			typedef std::weak_ptr<Base>	Base_w;

			typedef std::shared_ptr<Local>	Local_s;
			typedef std::weak_ptr<Local>	Local_w;

			typedef std::shared_ptr<Remote>	Remote_s;
			typedef std::weak_ptr<Remote>	Remote_w;

		}

		/** @brief %RigidBody */
		namespace RigidBody {
			class Base;
			class Local;
			class Remote;

			typedef std::shared_ptr<Base>	Base_s;
			typedef std::weak_ptr<Base>	Base_w;

			typedef std::shared_ptr<Local>	Local_s;
			typedef std::weak_ptr<Local>	Local_w;

			typedef std::shared_ptr<Remote>	Remote_s;
			typedef std::weak_ptr<Remote>	Remote_w;
		}

		/** @brief %RigidDynamic */
		namespace RigidDynamic {
			class Base;
			class Local;
			class Remote;

			typedef std::shared_ptr<Base>	Base_s;
			typedef std::weak_ptr<Base>	Base_w;

			typedef std::shared_ptr<Local>	Local_s;
			typedef std::weak_ptr<Local>	Local_w;

			typedef std::shared_ptr<Remote>	Remote_s;
			typedef std::weak_ptr<Remote>	Remote_w;
		}

		/** @brief %RigidStatic */
		namespace RigidStatic {
			class Base;
			class Local;
			class Remote;

			typedef std::shared_ptr<Base>	Base_s;
			typedef std::weak_ptr<Base>	Base_w;

			typedef std::shared_ptr<Local>	Local_s;
			typedef std::weak_ptr<Local>	Local_w;

			typedef std::shared_ptr<Remote>	Remote_s;
			typedef std::weak_ptr<Remote>	Remote_w;
		}

		class empty;


		typedef std::shared_ptr<Base>		Base_s;
		typedef std::weak_ptr<Base>		Base_w;
		typedef std::unique_ptr<Base>		Base_u;






		/** @brief Utilities */
		namespace Util {
			typedef int					index_type;

			class addr;

			typedef std::weak_ptr<addr>			addr_w;

			class Parent;

			typedef std::shared_ptr<Parent>			Parent_s;
			typedef std::weak_ptr<Parent>			Parent_w;
			typedef std::unique_ptr<Parent>			Parent_u;
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

				typedef std::shared_ptr<Base>		Base_s;
				typedef std::weak_ptr<Base>		Base_w;

				typedef std::shared_ptr<Manual>		Manual_s;
				typedef std::weak_ptr<Manual>		Manual_w;

			}
		}

		/** @brief %Event */
		namespace Event {
			class Base;
		}
	}
}

#endif
