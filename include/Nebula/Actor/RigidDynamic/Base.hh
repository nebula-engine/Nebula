#ifndef NEBULA_ACTOR_RIGID_DYNAMIC_BASE_HH
#define NEBULA_ACTOR_RIGID_DYNAMIC_BASE_HH

#include <Nebula/Actor/RigidBody/Base.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		namespace RigidDynamic {
			class Base: public Neb::Actor::RigidBody::Base {
				public:
					Base();
					Base(Neb::Actor::Util::Parent_s);

					virtual void				init();

			};
		}
	}
}


#endif








