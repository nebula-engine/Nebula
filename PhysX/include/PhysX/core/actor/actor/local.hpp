#ifndef PHYSX_CONTENT_ACTOR_ACTOR_LOCAL_HPP
#define PHYSX_CONTENT_ACTOR_ACTOR_LOCAL_HPP

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/Actor/Local.hh>

#include <PhysX/core/actor/local.hpp>
#include <PhysX/core/actor/actor/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace actor {



	class local:
		virtual public neb::core::actor::actor::local,
		virtual public phx::core::actor::local,
		virtual public phx::core::actor::actor::base
	{

		public:
			local(sp::shared_ptr<neb::core::actor::util::parent> parent);

			virtual void					init();
			virtual void					release();
			virtual void					step(neb::core::TimeStep const & ts);


			virtual void					create_physics() = 0;
			virtual void					init_physics() = 0;

			virtual void					add_force(real) = 0;
			virtual void					set_pose(physx::PxTransform);

			virtual int					fire();

			virtual sp::shared_ptr<phx::core::actor::rigiddynamic::base>		get_projectile() = 0;


			physx::PxActor*					px_actor_;

			//std::shared_ptr<neb::core::actor>		object_;
	};


}}}}

#endif


