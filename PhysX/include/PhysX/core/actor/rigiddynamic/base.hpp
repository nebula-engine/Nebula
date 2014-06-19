#ifndef __PX_CONTENT_ACTOR_RIGIDDYNAMIC_BASE_HPP
#define __PX_CONTENT_ACTOR_RIGIDDYNAMIC_BASE_HPP

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/RigidDynamic/Base.hh>

#include <PhysX/core/actor/rigidbody/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace rigiddynamic {



	class base:
		virtual public neb::core::actor::rigiddynamic::base,
		virtual public phx::core::actor::rigidbody::base
	{

		public:
			base(sp::shared_ptr<phx::core::actor::util::parent>);

			virtual void					init();
			virtual void					release();
			virtual void					step(neb::core::TimeStep const & ts);


			virtual void					create_physics() = 0;
			virtual void					init_physics() = 0;

			virtual void					add_force(real) = 0;
			//virtual void					setPose(neb::core::pose const & pose);


			//virtual sp::shared_ptr<phx::core::actor::rigiddynamic::base>		get_projectile() = 0;


	};


}}}}

#endif


