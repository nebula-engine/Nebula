#ifndef NEBULA_ACTOR_LOCAL_HH
#define NEBULA_ACTOR_LOCAL_HH

#include <Nebula/Actor/Base.hh>

namespace Neb {
	namespace Actor {
		class Local: virtual public Neb::Actor::Base {
			public:
				virtual void		stepBaseDerived(double const & time, double const & dt);

				template<class D, typename... Args> inline void		dispatch(Args... a) {
					Neb::Actor::Base::dispatch<D>(a...);
					D::visit(this, a...);
				}
		};
	}
}

#endif





