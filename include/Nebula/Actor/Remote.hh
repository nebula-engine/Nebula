#ifndef NEBULA_ACTOR_REMOTE_HH
#define NEBULA_ACTOR_REMOTE_HH

#include <Nebula/Actor/Base.hh>
namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		class Remote: virtual public neb::Actor::Base {
			public:
				virtual void		stepBaseDerived(double dt);
		};
	}
}

#endif



