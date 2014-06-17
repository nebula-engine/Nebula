#ifndef __PX_CONTENT_ACTOR_RIGIDACTOR_LOCAL_HPP__
#define __PX_CONTENT_ACTOR_RIGIDACTOR_LOCAL_HPP__

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/Actor/Base.hh>

#include <PhysX/core/actor/actor/local.hpp>
#include <PhysX/core/actor/rigidactor/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace rigidactor {



	class local:
		virtual public neb::core::actor::rigidactor::local,
		virtual public phx::core::actor::actor::local,
		virtual public phx::core::actor::rigidactor::base
	{

		public:
			local(sp::shared_ptr<neb::core::actor::util::parent>);

			virtual void					init();
			virtual void					release();
			virtual void					step(neb::core::TimeStep const & ts);


			virtual void					create_physics() = 0;
			virtual void					init_physics() = 0;

			virtual void					add_force(real) = 0;
			virtual void					set_pose(physx::PxTransform);


			virtual sp::shared_ptr<phx::core::actor::rigiddynamic::local>		get_projectile() = 0;


			physx::PxActor*					px_actor_;

			//std::shared_ptr<neb::core::actor>		object_;
	};


}}}}

#endif


