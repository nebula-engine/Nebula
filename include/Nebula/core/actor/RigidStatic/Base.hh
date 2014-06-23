#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__

#include <Nebula/core/actor/RigidActor/Base.hh>

namespace neb { namespace core { namespace actor {
		

	namespace rigidstatic {
		class base:
			virtual public neb::core::actor::rigidactor::base
		{
			public:
				base(sp::shared_ptr<neb::core::actor::util::parent> parent);


				virtual void	init();


				virtual void	step(gal::std::timestep const & ts);
		};
	}
}
}}

#endif


