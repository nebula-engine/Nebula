#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_rigid_static_plane_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_rigid_static_plane_HPP__



#include <nebula/content/actor/admin/rigid_static_plane.h>



namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace renderer
			{
				/// rigid dynamic
				class rigid_static_plane:
					public nebula::content::actor::admin::rigid_static
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					rigid_static_plane();
					/// Copy Ctor
					rigid_static_plane(const rigid_static_plane&);
					/// Dtor
					~rigid_static_plane();
					///@}

					///@name operator
					///@{
					/// assignment
					rigid_static_plane&							operator=(const rigid_static_plane&);
					///@}

				

					/// init
					virtual	void								init(const boost::shared_ptr<nebula::content::scene::admin::base>&);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step();
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








