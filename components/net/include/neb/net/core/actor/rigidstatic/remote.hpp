#ifndef PHYSX_CONTENT_ACTOR_RIGIDSTATIC_REMOTE_HPP
#define PHYSX_CONTENT_ACTOR_RIGIDSTATIC_REMOTE_HPP

#include <PxPhysicsAPI.h>

#include <neb/core/actor/RigidStatic/remote.hpp>

#include <PhysX/core/actor/rigidstatic/base.hpp>
#include <PhysX/core/actor/rigidactor/remote.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace rigidstatic {



	class remote:
		virtual public neb::core::actor::rigidstatic::remote,
		virtual public phx::core::actor::rigidactor::remote,
		virtual public phx::core::actor::rigidstatic::base
	{
		public:
			remote(std::shared_ptr<phx::core::actor::util::parent>);

			virtual void					init();
			virtual void					release();
			virtual void					step(gal::etc::timestep const & ts);



	};


}}}}

#endif




