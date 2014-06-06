#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__

#include <Nebula/Actor/RigidActor/Base.hh>

namespace Neb {
	namespace Actor {
		namespace RigidStatic {
			class Base: public Neb::Actor::RigidActor::Base {
				public:
					Base();
					Base(Neb::Actor::Util::Parent_s parent);


					virtual void	init();


					virtual void	step(Neb::Core::TimeStep const & ts);
			};
		}
	}
}

#endif


