#ifndef NEBULA_ACTOR_REMOTE_HH
#define NEBULA_ACTOR_REMOTE_HH

#include <Nebula/core/actor/Base.hh>

namespace neb { namespace core { namespace actor {


	class remote: virtual public neb::core::actor::base {
		public:
			remote(sp::shared_ptr<neb::core::actor::util::parent> parent);

			virtual void		step(gal::std::timestep const & ts);
	};


}
}}

#endif



