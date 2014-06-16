#ifndef __PX_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __PX_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/Actor/Base.hh>

#include <PhysX/core/actor/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace actor {



	class base:
		virtual public neb::core::actor::actor::base,
		virtual public phx::core::actor::base
	{

		public:
			base(sp::shared_ptr<phx::core::actor::util::parent>);

			virtual void					init();
			virtual void					release();
			virtual void					step(neb::core::TimeStep const & ts);


			virtual void					create_physics() = 0;
			virtual void					init_physics() = 0;

			//virtual void					add_force(real) = 0;
			virtual void					set_pose(mat4);
			
			virtual int					fire();
			
			virtual sp::shared_ptr<phx::core::actor::rigiddynamic::local>		get_projectile() = 0;
			
			
			physx::PxActor*					px_actor_;

			//std::shared_ptr<neb::core::actor>		object_;
	};


}}}}

#endif


