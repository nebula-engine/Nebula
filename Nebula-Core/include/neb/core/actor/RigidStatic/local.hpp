#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_LOCAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_LOCAL_HPP__

#include <neb/core/actor/RigidActor/Local.hh>
#include <neb/core/actor/RigidStatic/Base.hh>

namespace neb { namespace core { namespace actor { namespace rigidstatic {
		


	class local:
		virtual public neb::core::actor::rigidactor::local,
		virtual public neb::core::actor::rigidstatic::base
	{
		public:
			local(sp::shared_ptr<neb::core::actor::util::parent> parent);


			virtual void	init();
			virtual void	release();


			virtual void	step(gal::std::timestep const & ts);
	};



}}}}

#endif


