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

		// Core

		class Base;
		class Actor;
		class RigidActor;

		/** @brief %RigidBody @{ */
		namespace RigidBody {
			class RigidBody;
			typedef std::weak_ptr<RigidBody>	RigidBody_w;
		}

		class Rigid_Dynamic;
		class Rigid_Static;
		class empty;



		typedef std::shared_ptr<Base>		Base_s;
		typedef std::weak_ptr<Base>		Base_w;
		typedef std::unique_ptr<Base>		Base_u;


		typedef std::weak_ptr<RigidActor>	RigidActor_w;

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

				class Control;

				typedef std::shared_ptr<Control>	Control_s;
				typedef std::weak_ptr<Control>		Control_w;
				typedef std::unique_ptr<Control>	Control_u;

			}
		}
	}
	}

#endif
