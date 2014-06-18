#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_LOCAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_LOCAL_HPP__

#include <Nebula/Actor/RigidActor/Local.hh>
#include <Nebula/Actor/RigidStatic/Base.hh>

namespace neb { namespace core { namespace actor { namespace rigidstatic {
		


	class local:
		virtual public neb::core::actor::rigidactor::local,
		virtual public neb::core::actor::rigidstatic::base
	{
		public:
			local(sp::shared_ptr<neb::core::actor::util::parent> parent);


			virtual void	init();
			virtual void	release();


			virtual void	step(neb::core::TimeStep const & ts);
	};



}}}}

#endif


