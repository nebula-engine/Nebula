#ifndef NEBULA_CONTENT_ACTOR_RIGID_BODY_LOCAL_HH
#define NEBULA_CONTENT_ACTOR_RIGID_BODY_LOCAL_HH

#include <Nebula/Actor/Util/Types.hh>

#include <Nebula/Actor/RigidActor/Local.hh>
#include <Nebula/Actor/RigidBody/Base.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		namespace RigidBody {
			class Local:
				virtual public neb::Actor::RigidActor::Local,
				virtual public neb::Actor::RigidBody::Base
			{
				public:
					virtual void		step(neb::core::TimeStep const & ts);
	
			};
		}
	}
}

#endif


