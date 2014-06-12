#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_REMOTE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_REMOTE_HPP__

#include <Nebula/Actor/Remote.hh>
#include <Nebula/Actor/Actor/Base.hh>

namespace neb { namespace core { namespace actor {


	namespace actor {
		class Remote:
			virtual public neb::core::actor::actor::Base,
			virtual public neb::core::actor::Remote
		{
			public:
				virtual void		step(neb::core::TimeStep const & ts);
		};
	}
}
}}

#endif


