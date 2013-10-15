#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__

#include <nebula/content/actor/physics/rigid_actor.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// rigid dynamic
				class rigid_body:
					public nebula::content::actor::physics::rigid_actor
				{
					protected:
						/// copy ctor
						rigid_body(const rigid_body&);
						/// assignment
						rigid_body&								operator=(const rigid_body&);
					public:
						// ctor
						rigid_body( jess::shared_ptr<n34100::base> );
						/// dtor
						~rigid_body();
						/// init
						virtual	void								init();
						/// shutdown
						virtual	void								shutdown();
						/// update
						virtual	void								update();
						/// step
						virtual	void								step(float);
						/// render
						virtual	void								render( jess::shared_ptr<n23000::base> );
						/// density
						float									density_;
						/// velocity
						physx::PxVec3								velocity_;
				};
			}
		}
	}
}

#endif








