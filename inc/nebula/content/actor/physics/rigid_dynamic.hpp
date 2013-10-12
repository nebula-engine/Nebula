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
			public:
				///@name ctor and dtor
				///@{
				// Ctor
				rigid_dynamic();
				/// Copy Ctor
				rigid_dynamic(const rigid_dynamic&);
				/// Dtor
				~rigid_dynamic();
				///@}

				///@name operator
				///@{
				/// assignment
				rigid_dynamic&								operator=(const rigid_dynamic&);
				///@}

				

				/// init
				virtual	void								init( jess::shared_ptr<nebula::content::actor::admin::base> );
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








