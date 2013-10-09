#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_RIGID_STATIC_HPP__


#include <nebula/content/actor/renderer/rigid_actor.hpp>


namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace renderer
			{
				/// rigid static
				class rigid_static:
					public ncar::rigid_actor
				{
				public:
					/// ctor
					rigid_static();
					/// dtor
					~rigid_static();

					/// Initialize
					virtual	void						init( jess::shared_ptr<ncaa::base> );
					/// ShutDown
					virtual	void						shutdown();
					/// Update
					virtual	void						update();
					/// Render
					virtual	void						render( jess::shared_ptr<npr::base> );
					/// Step
					virtual	void						step( float );
					



					/// Create Shapes
					virtual	void						VCreateShape();


				};
			}
		}
	}
}


#endif





