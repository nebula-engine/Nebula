#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__

#include <Nebula/Actor/Base.hh>

namespace neb { namespace core { namespace actor {


	class Controller: public neb::core::actor::Base {
		public:
			Controller(sp::shared_ptr<neb::core::actor::Util::Parent>);
			virtual void		init();
			virtual void		release();
			virtual void		step(neb::core::TimeStep const & ts);
	};
}
}}



#endif

