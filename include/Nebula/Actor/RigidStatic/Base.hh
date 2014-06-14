#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__

#include <Nebula/Actor/RigidActor/Base.hh>

namespace neb { namespace core { namespace actor {
		

	namespace RigidStatic {
		class Base: public neb::core::actor::rigidactor::Base {
			public:
				Base();
				Base(sp::shared_ptr<neb::core::actor::Util::Parent> parent);


				virtual void	init();


				virtual void	step(neb::core::TimeStep const & ts);
		};
	}
}
}}

#endif


