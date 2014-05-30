#ifndef NEBULA_ACTOR_REMOTE_HH
#define NEBULA_ACTOR_REMOTE_HH

#include <Nebula/Actor/Base.hh>

namespace Neb {
	namespace Actor {
		class Remote: virtual public Neb::Actor::Base {
			public:
				virtual void		stepBaseDerived(double dt);
		};
	}
}

#endif



