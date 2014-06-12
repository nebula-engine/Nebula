#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__

#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		namespace RigidBody {
			class Base: virtual public neb::Actor::RigidActor::Base {
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








