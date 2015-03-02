#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__

#include <PxPhysicsAPI.h>

#include <neb/fnd/actor/base.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace controller {
	class Base:
		virtual public phx::core::actor::base,
		virtual public neb::core::actor::controller::base
	{
		public:
			Base(std::shared_ptr<neb::core::actor::util::parent>);
			virtual void		init();
			virtual void		release();
			virtual void		step(gal::etc::timestep const & ts);
			virtual void		add_force();
			physx::PxController*	px_controller_;
	};
}}}}}

#endif
