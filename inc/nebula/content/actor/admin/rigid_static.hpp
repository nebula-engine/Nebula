#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_STATIC_HPP__


#include <nebula/content/actor/admin/rigid_actor.hpp>


namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// rigid static
				class rigid_static:
					public nebula::content::actor::admin::rigid_actor
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
					virtual	void						render(const boost::shared_ptr<nebula::platform::renderer::base>&);
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





