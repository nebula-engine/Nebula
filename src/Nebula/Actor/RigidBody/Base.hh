#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__

#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

namespace Neb {
	namespace Actor {
		namespace RigidBody {
			class Base: virtual public Neb::Actor::RigidActor::Base {
				public:
					Base();
					Base(Neb::Actor::Util::Parent_s);

					virtual void					init();


					virtual Neb::Actor::Base_s			get_projectile();

				protected:
					virtual void					step(double dt);

					virtual void					add_force(double);
				public:
					virtual void					print_info();


					virtual void					create_physics() = 0;

					// control
					//virtual void					create_control(
					//		Neb::Actor::Control::RigidBody::Raw_s);
					void						setControl(Neb::Actor::Control::RigidBody::Base_s);
				public:
					Neb::Actor::Control::RigidBody::Base_s		control_;
				private:
					physx::PxVec3			force_;
					physx::PxVec3			torque_;
			};
		}
	}
}

#endif








