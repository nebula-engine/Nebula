#ifndef __PX_CONTENT_ACTOR_RIGIDSTATIC_BASE_HPP
#define __PX_CONTENT_ACTOR_RIGIDSTATIC_BASE_HPP

#include <PxPhysicsAPI.h>

#include <gal/stl/verbosity.hpp>

#include <neb/phx/core/actor/rigidactor/base.hpp>
#include <neb/phx/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace rigidstatic {
	/** @brief base */
	class base:
		public gal::tmp::Verbosity<neb::phx::core::actor::rigidstatic::base>,
		virtual public neb::phx::core::actor::rigidactor::base
	{

		public:
			using CHILD::get_fnd_app;
			using gal::tmp::Verbosity<neb::phx::core::actor::rigidstatic::base>::printv;
			virtual void					init(parent_t * const & p);
			virtual void					release();
			virtual void					step(gal::etc::timestep const & ts);
			virtual void					create_physics();
			virtual void					init_physics();
	};
}}}}}

#endif


