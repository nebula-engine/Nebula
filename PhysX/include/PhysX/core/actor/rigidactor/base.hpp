#ifndef PX_CONTENT_ACTOR_RIGIDACTOR_BASE_HPP
#define PX_CONTENT_ACTOR_RIGIDACTOR_BASE_HPP

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/Actor/Base.hh>

#include <PhysX/core/actor/actor/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace px { namespace core { namespace actor { namespace rigidactor {



	class base:
		virtual public neb::core::actor::rigidactor::base,
		virtual public px::core::actor::actor::base
	{

		public:
			base(sp::shared_ptr<neb::core::actor::util::parent>);

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


