#ifndef PHYSX_CONTENT_ACTOR_ACTOR_REMOTE_HPP
#define PHYSX_CONTENT_ACTOR_ACTOR_REMOTE_HPP

#include <PxPhysicsAPI.h>

#include <neb/core/actor/Actor/Remote.hh>

#include <PhysX/core/actor/remote.hpp>
#include <PhysX/core/actor/actor/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace actor {



	class remote:
		virtual public neb::core::actor::actor::remote,
		virtual public phx::core::actor::remote,
		virtual public phx::core::actor::actor::base
	{

		public:
			remote(sp::shared_ptr<phx::core::actor::util::parent> parent);

			virtual void					init();
			virtual void					release() = 0;
			virtual void					step(gal::std::timestep const & ts);


			//virtual void					create_physics() = 0;
			//virtual void					init_physics() = 0;

			//virtual void					add_force(real) = 0;
			//virtual void					set_pose(mat4);



	};


}}}}

#endif


