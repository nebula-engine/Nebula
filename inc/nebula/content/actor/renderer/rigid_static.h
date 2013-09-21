#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_RIGID_STATIC_HPP__


#include <nebula/content/actor/admin/rigid_actor.hpp>


namespace nebula
{
	namespace Content
	{
		namespace actor
		{
			namespace renderer
			{
				/// rigid static
				class rigid_static:
					public rigid_actor
				{
				public:
					/// ctor
					rigid_static();
					/// dtor
					~rigid_static();

					/// Initialize
					virtual	void						init();
					/// ShutDown
					virtual	void						shutDown();
					/// Update
					virtual	void						update();
					/// Render
					virtual	void						render(const boost::shared_ptr<>&);
					/// Step
					virtual	void						step();
					



					/// Create Shapes
					virtual	void						VCreateShape();


				};
			}
		}
	}
}


#endif





