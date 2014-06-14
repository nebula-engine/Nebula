#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <Nebula/Actor/Actor/Base.hh>

namespace neb { namespace core { namespace actor {
		namespace rigidactor {
			class base: virtual public neb::core::actor::actor::base {
				public:
					base();
					base(sp::shared_ptr<neb::core::actor::util::parent> parent);

					virtual void					init();
					virtual void					release();
					virtual void					step(neb::core::TimeStep const & ts);

			};
		}
}}}

#endif








