#ifndef __PX_CONTENT_ACTOR_RIGIDBODY_BASE_HPP
#define __PX_CONTENT_ACTOR_RIGIDBODY_BASE_HPP

#include <PxPhysicsAPI.h>

#include <Nebula/core/actor/RigidBody/Base.hh>
#include <Nebula/core/pose.hpp>

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
			virtual void					setPose(neb::core::pose const & pose);



			void									create_control(sp::shared_ptr<neb::gfx::window::base> window);

			
		public:

			sp::shared_ptr<phx::core::actor::control::rigidbody::base>	control_;


			vec3		force_;
			vec3		torque_;
	};


}}}}

#endif


