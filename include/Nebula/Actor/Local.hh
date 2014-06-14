#ifndef NEBULA_ACTOR_LOCAL_HH
#define NEBULA_ACTOR_LOCAL_HH


#include <Nebula/Actor/Base.hh>
#include <Nebula/Core/TimeStep.hpp>

namespace neb { namespace core { namespace actor {


	class local: virtual public neb::core::actor::base {
		public:
			local(sp::shared_ptr<neb::core::actor::util::parent> parent);
		
			virtual void		step(neb::core::TimeStep const & ts);
	};

}
}}

#endif





