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
				protected:
				public:
					/// ctor
					rigid_static( jess::shared_ptr<n32100::base> );
					/// dtor
					~rigid_static();
					/// Initialize
					virtual	void						init();
					/// ShutDown
					virtual	void						shutdown();
					/// Update
					virtual	void						update();
					/// Render
					virtual	void						render( jess::shared_ptr<n23000::base> );
					/// Step
					virtual	void						step(float);
					



					/// Create Shapes
					virtual	void						VCreateShape();


				};
			}
		}
	}
}


#endif





