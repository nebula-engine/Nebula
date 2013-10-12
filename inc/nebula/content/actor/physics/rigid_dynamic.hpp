#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__



#include <nebula/content/actor/physics/rigid_body.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// rigid dynamic
				class rigid_dynamic:
					public nebula::content::actor::physics::rigid_body
				{
					protected:
						/// copy ctor
						rigid_dynamic(const rigid_dynamic&);
						/// assignment
						rigid_dynamic&								operator=(const rigid_dynamic&);
					public:
						// ctor
						rigid_dynamic( jess::shared_ptr<n34100::base> );
						/// dtor
						~rigid_dynamic();
						/// init
						virtual	void								init();
						/// shutdown
						virtual	void								shutdown();
						/// update
						virtual	void								update();
						/// step
						virtual	void								step(float);
						/// render
						virtual	void								render( jess::shared_ptr<nebula::platform::renderer::base> );
						/// create shapes
						virtual	void								create_shape();
				};
			}
		}
	}
}

#endif








