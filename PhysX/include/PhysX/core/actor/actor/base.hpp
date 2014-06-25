#ifndef __PX_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __PX_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <neb/core/actor/Actor/Base.hh>
#include <neb/core/pose.hpp>

#include <PhysX/core/actor/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace actor {



	class base:
		virtual public neb::core::actor::actor::base,
		virtual public phx::core::actor::base
	{

		public:
			base(sp::shared_ptr<phx::core::actor::util::parent>);
			virtual ~base();

			virtual void					init();
			virtual void					release() = 0;
		protected:
			void						releaseUp();
		public:	
			virtual void					step(gal::std::timestep const & ts);


			virtual void					create_physics() = 0;
			virtual void					init_physics() = 0;

			//virtual void					add_force(real) = 0;

			virtual void					setPose(neb::core::pose const & pose);



		public:


			physx::PxActor*					px_actor_;

	};


}}}}

#endif


