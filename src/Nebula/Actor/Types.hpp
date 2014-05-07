#ifndef NEBULA_ACTOR_TYPES_HPP
#define NEBULA_ACTOR_TYPES_HPP

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
		
		/** @name Util @{ */
		class id;
		class addr;
		class raw;
		class desc;
		class parent;
		/** @} */


		class Base;
		class Actor;
		class RigidActor;

		/** @name %RigidBody @{ */
		namespace RigidBody {
			class RigidBody;
			typedef boost::shared_ptr<RigidBody>	RigidBody_s;
		}
		/** @} */

		class Rigid_Dynamic;
		class Rigid_Static;
		class empty;
		
		
		
		typedef boost::shared_ptr<raw>		raw_s;
		
		typedef boost::shared_ptr<Base>		Base_s;
		typedef Neb::weak_ptr<Base>		Base_w;

		typedef boost::shared_ptr<RigidActor>	RigidActor_s;
		
		


		typedef std::shared_ptr<id>		id_s;
		typedef std::shared_ptr<addr>		addr_s;
		typedef std::shared_ptr<desc>		desc_s;
		

		typedef std::shared_ptr<parent>		parent_s;
		typedef std::weak_ptr<parent>		parent_w;

	}
}

#endif
