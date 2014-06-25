#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__

#include <memory>


//#include <tinyxml/tinyxml.h>

//#include <math/transform.hpp>

#include <gal/std/timestep.hpp>

#include <neb/core/actor/Base.hh>
#include <neb/core/actor/Util/Types.hh>

namespace neb { namespace core { namespace actor {


	class empty: public neb::core::actor::base {
		public:
			empty(sp::shared_ptr<neb::core::actor::util::parent>);
			virtual void			init();
			virtual void			release() {}
			virtual void			step(gal::std::timestep const & ts) {}
	};



}}}


#endif


