#ifndef NEBULA_ACTOR_LOCAL_HH
#define NEBULA_ACTOR_LOCAL_HH


#include <Nebula/Actor/Base.hh>
#include <Nebula/Core/TimeStep.hpp>

namespace neb { namespace core { namespace actor {


	class local: virtual public neb::core::actor::Base {
		public:
			virtual void		step(neb::core::TimeStep const & ts);
	};

}
}}

#endif





