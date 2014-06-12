#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <Nebula/Util/typedef.hpp>
#include <Nebula/Actor/Base.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		namespace Actor {
			class Base: virtual public neb::Actor::Base {
				public:
					Base();
					Base(sp::shared_ptr<neb::Actor::Util::Parent>;
					
					virtual void			init();
					virtual void			release();
					virtual void			step(neb::core::TimeStep const & ts);
					
					virtual void			set_pose(mat4);
			};
		}
	}
}

#endif


