#ifndef PHYSX_CONTENT_ACTOR_RIGIDBODY_LOCAL_HPP
#define PHYSX_CONTENT_ACTOR_RIGIDBODY_LOCAL_HPP

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/RigidBody/Local.hh>

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
			virtual void					release();
			virtual void					step(neb::core::TimeStep const & ts);
			
			
			virtual void					create_physics() = 0;
			virtual void					init_physics() = 0;
			
			virtual void					add_force(real) = 0;
			//virtual void					set_pose(physx::PxTransform);
			
			/** @brief projectile
			 *
			 * @note required because of diamond inheritance
			 */
			virtual sp::shared_ptr<phx::core::actor::rigiddynamic::local>		get_projectile();
			
			physx::PxActor*					px_actor_;

			//std::shared_ptr<neb::core::actor>		object_;
	};


}}}}

#endif


