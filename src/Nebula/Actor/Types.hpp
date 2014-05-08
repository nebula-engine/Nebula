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

		typedef Neb::weak_ptr<raw>		raw_w;
		typedef Neb::weak_ptr<addr>		addr_w;
		typedef Neb::weak_ptr<desc>		desc_w;


		typedef Neb::weak_ptr<parent>		parent_w;

		/** @brief %Control */
		namespace control {
			namespace rigid_body {
				enum type {
					NONE = 0,
					T0,
					T1,
				};

				class raw;
				typedef boost::shared_ptr<raw>          raw_s;

				class control;
				typedef boost::shared_ptr<control>      control_s;

			}
		}
	}
	}

#endif
