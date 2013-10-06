#ifndef __BOX_CLIENT_CONTENT_SCENE_ADMIN_BASE_HPP__
#define __BOX_CLIENT_CONTENT_SCENE_ADMIN_BASE_HPP__

#include <box_client/ns.hpp>

#include <nebula/content/scene/admin/base.hpp>


namespace box_client
{
	namespace content
	{
		namespace scene
		{
			namespace admin
			{
				/// base
				class base:
					public nc_sc_a::base
				{
				public:
					/// init
					virtual void						init( jess::shared_ptr<ncua::base> );
					/// box get view
					jess::shared_ptr<bc33100::base>				get_view()
					{
						return view_;
					}
					///@name references
					///@{
					/// view
					jess::shared_ptr<bc33100::base>				view_;
					/// rigid dynamic box
					jess::shared_ptr<ncaa::rigid_dynamic_box>		rigid_dyn_box_;
					/// controller
					jess::shared_ptr<ncaa::controller>			ctrlr_;
					///@}
					
					
					
				};
			}
		}
	}
}

#endif
