#ifndef PHYSX_CORE_ACTOR_RIGIDDYNAMIC_LOCAL_HPP
#define PHYSX_CORE_ACTOR_RIGIDDYNAMIC_LOCAL_HPP

#include <PxPhysicsAPI.h>


#include <PhysX/core/actor/rigidbody/local.hpp>
#include <PhysX/core/actor/rigiddynamic/base.hpp>

#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace rigiddynamic {


	class local:
		virtual public phx::core::actor::rigidbody::local,
		virtual public phx::core::actor::rigiddynamic::base
	{

		public:
			local(sp::shared_ptr<phx::core::actor::util::parent>);

			virtual void					init();

			virtual void					release();
		protected:
			//void						releaseUp();
		public:

			virtual void					step(gal::std::timestep const & ts);


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


