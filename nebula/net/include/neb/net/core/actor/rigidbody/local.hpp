#ifndef PHYSX_CONTENT_ACTOR_RIGIDBODY_LOCAL_HPP
#define PHYSX_CONTENT_ACTOR_RIGIDBODY_LOCAL_HPP

#include <PxPhysicsAPI.h>

#include <neb/core/actor/RigidBody/Local.hh>

#include <PhysX/core/actor/rigidactor/local.hpp>
#include <PhysX/core/actor/rigidbody/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace rigidbody {



	class local:
		virtual public neb::core::actor::rigidbody::local,
		virtual public phx::core::actor::rigidactor::local,
		virtual public phx::core::actor::rigidbody::base
	{
		public:
			local(sp::shared_ptr<phx::core::actor::util::parent>);

			virtual void					init();
			virtual void					release() = 0;
			virtual void					step(gal::std::timestep const & ts);
			
			
			//virtual void					create_physics() = 0;
			//virtual void					init_physics() = 0;
			
			//virtual void					add_force(real) = 0;
			//virtual void					set_pose(physx::PxTransform);
			
			
	};


}}}}

#endif


