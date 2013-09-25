#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_BOX_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_BOX_HPP__



#include <nebula/content/actor/physics/rigid_dynamic.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// rigid dynamic
				class rigid_dynamic_box:
					public nebula::content::actor::physics::rigid_dynamic
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					rigid_dynamic_box();
					/// Copy Ctor
					rigid_dynamic_box(const rigid_dynamic_box&);
					/// Dtor
					~rigid_dynamic_box();
					///@}

					///@name operator
					///@{
					/// assignment
					rigid_dynamic_box&							operator=(const rigid_dynamic_box&);
					///@}

				

					/// init
					virtual	void								init(const boost::shared_ptr<nebula::content::actor::admin::base>&);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step(FLOAT);
					/// render
					virtual	void								render(const boost::shared_ptr<nebula::platform::renderer::base>&);
				
				
				
				
					/// create shapes
					virtual	void								create_shape();
				};
			}
		}
	}
}

#endif








