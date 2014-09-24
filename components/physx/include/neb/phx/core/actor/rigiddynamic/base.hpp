#ifndef __PX_CONTENT_ACTOR_RIGIDDYNAMIC_BASE_HPP
#define __PX_CONTENT_ACTOR_RIGIDDYNAMIC_BASE_HPP

#include <PxPhysicsAPI.h>


#include <neb/phx/core/actor/rigidbody/base.hpp>
#include <neb/phx/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace rigiddynamic {



	class base:
		virtual public neb::phx::core::actor::rigidbody::base
	{

		public:
			base(std::shared_ptr<neb::phx::core::actor::util::parent>);

			virtual void					init();
			virtual void					release() = 0;
		public:
			virtual void					step(gal::etc::timestep const & ts) = 0;


			virtual void					create_physics();
			virtual void					init_physics();

			//virtual void					add_force(double) = 0;
			//virtual void					setPose(neb::core::pose const & pose);




	};


}}}}}

#endif


