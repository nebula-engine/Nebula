#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_LOCAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_LOCAL_HPP__


#include <neb/core/actor/Local.hh>
#include <neb/core/actor/Actor/Base.hh>

namespace neb { namespace core { namespace actor {
		


namespace actor {
			class local:
				virtual public neb::core::actor::actor::base,
				virtual public neb::core::actor::local
			{
				public:
					local(sp::shared_ptr<neb::core::actor::util::parent> parent);
				
					virtual void		step(gal::std::timestep const & ts);
			};


}		}
	}
}

#endif


