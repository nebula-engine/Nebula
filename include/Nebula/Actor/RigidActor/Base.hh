#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <Nebula/Actor/Actor/Base.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		namespace RigidActor {
			class Base: virtual public Neb::Actor::Actor::Base {
				public:
					Base();
					Base(Neb::Actor::Util::Parent_s);

					virtual void					init();
					virtual void					release();
					virtual void					step(Neb::Core::TimeStep const & ts);

			};
		}
	}
}

#endif








