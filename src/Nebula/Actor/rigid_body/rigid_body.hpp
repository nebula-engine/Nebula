#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__

#include <Nebula/Actor/Types.hpp>
#include <Nebula/Actor/Rigid_Actor.hpp>

namespace Neb {
	namespace Actor {
		namespace RigidBody {
			class RigidBody: public Neb::Actor::RigidActor {
				public:
					RigidBody(Neb::Actor::parent_w);
					
					

					//virtual void					init(Neb::Actor::desc_w);
					
					
					
					virtual Neb::Actor::Base_s			get_projectile();
					
				private:
					virtual void					step_local(double);
					virtual void					step_remote(double);

					virtual void					add_force(double);
				public:
					virtual void					print_info();


					virtual void					create_physics() = 0;
					
					// control
					virtual void					create_control(
							Neb::Actor::Control::RigidBody::Raw_s);
				public:
					Neb::Actor::Control::RigidBody::Control_w	control_;
				private:
					physx::PxVec3			force_;
					physx::PxVec3			torque_;
			};
		}
	}
}

#endif








