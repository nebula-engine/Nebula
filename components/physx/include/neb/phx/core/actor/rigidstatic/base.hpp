#ifndef __PX_CONTENT_ACTOR_RIGIDSTATIC_BASE_HPP
#define __PX_CONTENT_ACTOR_RIGIDSTATIC_BASE_HPP

#include <PxPhysicsAPI.h>


#include <neb/phx/core/actor/rigidactor/base.hpp>
#include <neb/phx/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace rigidstatic {
	/** @brief base */
	class base:
		virtual public neb::phx::core::actor::rigidactor::base
	{

		public:
			//base(std::shared_ptr<neb::phx::core::actor::util::parent>);

			//virtual void					init() = 0;
			//virtual void					release() = 0;
			virtual void					step(gal::etc::timestep const & ts) = 0;


			virtual void					create_physics();
			virtual void					init_physics();
	};
}}}}}

#endif


