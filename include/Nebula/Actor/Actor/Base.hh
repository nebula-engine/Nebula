#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <Nebula/Util/typedef.hpp>
#include <Nebula/Actor/Base.hh>

namespace neb { namespace core { namespace actor {
	namespace actor {
		class base: virtual public neb::core::actor::base {
			public:
				//base();
				base(sp::shared_ptr<neb::core::actor::util::parent> parent);

				virtual void			init();
				virtual void			release();
				virtual void			step(neb::core::TimeStep const & ts);

				virtual void			set_pose(mat4);
		};
	}
}}}

#endif


