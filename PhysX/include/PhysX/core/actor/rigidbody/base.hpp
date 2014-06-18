#ifndef __PX_CONTENT_ACTOR_RIGIDBODY_BASE_HPP
#define __PX_CONTENT_ACTOR_RIGIDBODY_BASE_HPP

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/Core/pose.hpp>

#include <PhysX/core/actor/rigidactor/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace rigidbody {


	/** @brief base */
	class base:
		virtual public neb::core::actor::rigidbody::base,
		virtual public phx::core::actor::rigidactor::base
	{

		public:
			base(sp::shared_ptr<phx::core::actor::util::parent>);

			virtual void					init();
			virtual void					release();
			virtual void					step(neb::core::TimeStep const & ts);


			virtual void					create_physics() = 0;
			virtual void					init_physics() = 0;

			virtual void					add_force(real) = 0;
			virtual void					set_pose(neb::core::pose const & pose);


			virtual sp::shared_ptr<phx::core::actor::rigiddynamic::local>		get_projectile() = 0;


			//physx::PxActor*					px_actor_;

			//std::shared_ptr<neb::core::actor>		object_;
			
		public:

			sp::shared_ptr<phx::core::actor::control::rigidbody::base>	control_;


			vec3		force_;
			vec3		torque_;
	};


}}}}

#endif


