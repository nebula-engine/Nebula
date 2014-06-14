#ifndef NEBULA_ACTOR_REMOTE_HH
#define NEBULA_ACTOR_REMOTE_HH

#include <Nebula/Actor/Base.hh>

namespace neb { namespace core { namespace actor {


	class Remote: virtual public neb::core::actor::base {
		public:
			virtual void		step(neb::core::TimeStep const & ts);
	};


}
}}

#endif



