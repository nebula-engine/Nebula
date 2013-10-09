#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_STATIC_HPP__


#include <nebula/content/actor/physics/rigid_actor.hpp>


namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// rigid static
				class rigid_static:
					virtual public ncap::rigid_actor
				{
				public:
					/// ctor
					rigid_static();
					/// dtor
					~rigid_static();

					/// Initialize
					virtual	void						init( jess::shared_ptr<nebula::content::actor::admin::base> );
					/// ShutDown
					virtual	void						shutdown();
					/// Update
					virtual	void						update();
					/// Render
					virtual	void						render( jess::shared_ptr<nebula::platform::renderer::base> );
					/// Step
					virtual	void						step( FLOAT );
					
					
					
					
					/// Create Shapes
					virtual	void						create_shape();
					
					
				};
			}
		}
	}
}


#endif





