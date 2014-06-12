#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_LOCAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_LOCAL_HPP__


#include <Nebula/Actor/Local.hh>
#include <Nebula/Actor/Actor/Base.hh>

namespace neb {
	namespace Actor {
		namespace Actor {
			class Local:
				virtual public Neb::Actor::Actor::Base,
				virtual public Neb::Actor::Local
			{
				public:
					virtual void		step(Neb::Core::TimeStep const & ts);
			};
		}
	}
}

#endif


