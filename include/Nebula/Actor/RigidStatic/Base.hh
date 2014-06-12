#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__

#include <Nebula/Actor/RigidActor/Base.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		namespace RigidStatic {
			class Base: public neb::Actor::RigidActor::Base {
				public:
					Base();
					Base(neb::Actor::Util::Parent_s parent);


					virtual void	init();


					virtual void	step(neb::core::TimeStep const & ts);
			};
		}
	}
}

#endif


