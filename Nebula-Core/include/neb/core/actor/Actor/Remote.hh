#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_REMOTE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_REMOTE_HPP__

#include <neb/core/actor/Remote.hh>
#include <neb/core/actor/Actor/Base.hh>

namespace neb { namespace core { namespace actor {


	namespace actor {
		class remote:
			virtual public neb::core::actor::actor::base,
			virtual public neb::core::actor::remote
		{
			public:
				remote(sp::shared_ptr<neb::core::actor::util::parent> parent);

				virtual void		step(gal::std::timestep const & ts);
		};
	}
}
}}

#endif


