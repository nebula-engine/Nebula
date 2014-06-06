#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <glm/mat4x4.hpp>

#include <Nebula/Actor/Base.hh>

namespace Neb {
	namespace Actor {
		namespace Actor {
			class Base: virtual public Neb::Actor::Base {
				public:
					Base();
					Base(Neb::Actor::Util::Parent_s);
					
					virtual void			init();
					virtual void			release();
					virtual void			step(Neb::Core::TimeStep const & ts);
					
					virtual void			set_pose(mat4);
					virtual int			fire();

					virtual Neb::Actor::Base_s	get_projectile() = 0;
			};
		}
	}
}

#endif


