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
					public n32100::base
				{
				public:
					/// ctor
					base( jess::shared_ptr<n31100::base> );
					/// init
					virtual void						init( jess::shared_ptr<n31100::base> );
					/// box get view
					jess::shared_ptr<bc33100::base>				get_view()
					{
						return view_;
					}
					///@name referen30000es
					///@{
					/// view
					jess::shared_ptr<bc33100::base>				view_;
					/// rigid dynamic box
					jess::shared_ptr<n34100::rigid_dynamic_box>		rigid_dyn_box_;
					/// rigid static plane
					jess::shared_ptr<n34100::rigid_static_plane>		rigid_sta_pln_;
					/// controller
					jess::shared_ptr<n34100::controller>			ctrlr_;
					///@}
					
					
					
				};
			}
		}
	}
}

#endif
