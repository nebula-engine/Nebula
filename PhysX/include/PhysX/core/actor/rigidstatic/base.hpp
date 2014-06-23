#ifndef __PX_CONTENT_ACTOR_RIGIDSTATIC_BASE_HPP
#define __PX_CONTENT_ACTOR_RIGIDSTATIC_BASE_HPP

#include <PxPhysicsAPI.h>

#include <Nebula/core/actor/RigidStatic/Base.hh>

#include <PhysX/core/actor/rigidactor/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace rigidstatic {


	/** @brief base */
	class base:
		virtual public neb::core::actor::rigidstatic::base,
		virtual public phx::core::actor::rigidactor::base
	{

		public:
			base(sp::shared_ptr<phx::core::actor::util::parent>);

			virtual void					init();
			virtual void					release();
			virtual void					step(gal::std::timestep const & ts);


			virtual void					create_physics();
			virtual void					init_physics();




	};


}}}}

#endif


