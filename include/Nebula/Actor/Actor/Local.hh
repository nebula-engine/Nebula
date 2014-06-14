#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_LOCAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_LOCAL_HPP__


#include <Nebula/Actor/Local.hh>
#include <Nebula/Actor/Actor/Base.hh>

namespace neb { namespace core { namespace actor {
		


namespace actor {
			class local:
				virtual public neb::core::actor::actor::Base,
				virtual public neb::core::actor::local
			{
				public:
					virtual void		step(neb::core::TimeStep const & ts);
			};


}		}
	}
}

#endif


