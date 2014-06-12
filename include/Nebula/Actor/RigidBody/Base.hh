#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__

#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

namespace neb {
	namespace Actor {
		namespace RigidBody {
			class Base: virtual public Neb::Actor::RigidActor::Base {
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








