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
					public boost::enable_shared_from_this<bc32100::base>,
					public nc_sc_a::base
				{
				public:
					/// init
					virtual void						init( boost::shared_ptr<ncua::base>& );
					/// box get view
					jess::shared_ptr<bc33100::base>				get_view() { return view_; }
					
					///@name references
					///{
					/// view
					jess::shared_ptr<bc33100::base>				view_;
					/// rigid dynamic box
					boost::shared_ptr<ncaa::rigid_dynamic_box>		rigid_dyn_box_;
					/// controller
					boost::shared_ptr<ncaa::controller>			ctrlr_;
					///}
					
					
					

				};
			}
		}
	}
}
#endif
