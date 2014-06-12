#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__

#include <Nebula/Actor/Base.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		class Controller: public neb::Actor::Base {
			public:
				Controller(sp::shared_ptr<neb::Actor::Util::Parent>;
				virtual void		init();
				virtual void		release();
				virtual void		step(neb::core::TimeStep const & ts);
		};
	}
}



#endif

