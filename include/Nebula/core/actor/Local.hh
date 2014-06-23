#ifndef NEBULA_ACTOR_LOCAL_HH
#define NEBULA_ACTOR_LOCAL_HH


#include <Nebula/core/actor/Base.hh>
#include <gal/std/timestep.hpp>

namespace neb { namespace core { namespace actor {


	class local: virtual public neb::core::actor::base {
		public:
			local(sp::shared_ptr<neb::core::actor::util::parent> parent);
		
			virtual void		step(gal::std::timestep const & ts);
	};

}
}}

#endif





