#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <Nebula/util/typedef.hpp>
#include <Nebula/core/actor/Base.hh>

namespace neb { namespace core { namespace actor {
	namespace actor {
		class base: virtual public neb::core::actor::base {
			public:
				//base();
				base(sp::shared_ptr<neb::core::actor::util::parent> parent);

				virtual void			init();
				virtual void			release();
				virtual void			step(gal::std::timestep const & ts);

				virtual void			setPose(neb::core::pose const & pose);
		};
	}
}}}

#endif


