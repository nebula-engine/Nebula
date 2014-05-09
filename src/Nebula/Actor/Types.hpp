#ifndef NEBULA_ACTOR_TYPES_HPP
#define NEBULA_ACTOR_TYPES_HPP

#include <Nebula/Memory/smart_ptr.hpp>

namespace Neb {
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

		class addr;
		class raw;
		class desc;
		class parent;


		class Base;
		class Actor;
		class RigidActor;

		/** @brief %RigidBody @{ */
		namespace RigidBody {
			class RigidBody;
			typedef Neb::weak_ptr<RigidBody>	RigidBody_w;
		}

		class Rigid_Dynamic;
		class Rigid_Static;
		class empty;




		typedef Neb::weak_ptr<Base>		Base_w;
		typedef Neb::unique_ptr<Base>		Base_u;


		typedef Neb::weak_ptr<RigidActor>	RigidActor_w;

		// Util
		typedef Neb::unique_ptr<raw>		raw_u;
		typedef Neb::weak_ptr<raw>		raw_w;


		typedef Neb::weak_ptr<addr>		addr_w;


		typedef Neb::unique_ptr<desc>		desc_u;
		typedef Neb::weak_ptr<desc>		desc_w;


		typedef Neb::weak_ptr<parent>		parent_w;

		/** @brief %Control */
		namespace Control {
			namespace RigidBody {
				enum Type {
					NONE = 0,
					T0,
					T1,
				};

				class Raw;
				typedef boost::shared_ptr<raw>		Raw_s;

				class Control;

				typedef Neb::unique_ptr<Control>	Control_u;
				typedef Neb::weak_ptr<Control>		Control_w;

			}
		}
	}
	}

#endif
