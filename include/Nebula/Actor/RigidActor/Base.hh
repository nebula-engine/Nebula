#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <Nebula/Actor/Actor/Base.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		namespace RigidActor {
			class Base: virtual public neb::Actor::Actor::Base {
				public:
					Base();
					Base(sp::shared_ptr<neb::Actor::Util::Parent>;

					virtual void					init();
					virtual void					release();
					virtual void					step(neb::core::TimeStep const & ts);

			};
		}
	}
}

#endif








