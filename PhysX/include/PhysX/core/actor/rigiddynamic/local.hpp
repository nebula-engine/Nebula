#ifndef PHYSX_CORE_ACTOR_RIGIDDYNAMIC_LOCAL_HPP
#define PHYSX_CORE_ACTOR_RIGIDDYNAMIC_LOCAL_HPP

#include <PxPhysicsAPI.h>

#include <Nebula/core/actor/RigidDynamic/Local.hh>

#include <PhysX/core/actor/rigidbody/local.hpp>
#include <PhysX/core/actor/rigiddynamic/base.hpp>

#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace rigiddynamic {


	class local:
		virtual public neb::core::actor::rigiddynamic::local,
		virtual public phx::core::actor::rigidbody::local,
		virtual public phx::core::actor::rigiddynamic::base
	{

		public:
			local(sp::shared_ptr<phx::core::actor::util::parent>);

			virtual void					init();
			virtual void					release();
			virtual void					step(neb::core::TimeStep const & ts);


			virtual void					create_physics();
			virtual void					init_physics();

			virtual void					add_force(real);
			virtual void					setPose(neb::core::pose const & pose);


			/** @brief projectile
			 *
			 * @note required because of diamond inheritance
			 */

	};


}}}}

#endif


