#ifndef __PX_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __PX_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/Actor/Base.hh>

#include <PhysX/core/actor/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace px { namespace core { namespace actor { namespace rigidbody {



	class base:
		virtual public neb::core::actor::rigidbody::local,
		virtual public px::core::actor::rigidactor::local,
		virtual public px::core::actor::rigidbody::base
	{

		public:
			base(sp::shared_ptr<neb::core::actor::Util::Parent>);

			virtual void					init();
			virtual void					release();
			virtual void					step(neb::core::TimeStep const & ts);


			virtual void					create_physics() = 0;
			virtual void					init_physics() = 0;

			virtual void					add_force(real) = 0;
			virtual void					set_pose(physx::PxTransform);

			virtual int					fire();

			virtual sp::shared_ptr<px::core::actor::rigiddynamic::base>		get_projectile() = 0;


			physx::PxActor*					px_actor_;

			//std::shared_ptr<neb::core::actor>		object_;
	};


}}}}

#endif


