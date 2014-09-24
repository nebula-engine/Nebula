#ifndef __PX_CONTENT_ACTOR_RIGIDACTOR_LOCAL_HPP__
#define __PX_CONTENT_ACTOR_RIGIDACTOR_LOCAL_HPP__

#include <PxPhysicsAPI.h>

#include <neb/core/actor/RigidActor/Local.hh>

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
			local(std::shared_ptr<phx::core::actor::util::parent>);

			virtual void					init();
			virtual void					release() = 0;
			virtual void					step(gal::etc::timestep const & ts);


			//virtual void					create_physics() = 0;
			//virtual void					init_physics() = 0;

			//virtual void					add_force(real) = 0;
			//virtual void					set_pose(physx::PxTransform);





	};


}}}}

#endif


