#ifndef __BOX_CLIENT_CONTENT_VIEW_ADMIN_HPP__
#define __BOX_CLIENT_CONTENT_VIEW_ADMIN_HPP__

#include <box_client/util/types/content/types.hpp>

#include <nebula/content/view/admin/base.hpp>

namespace box_client
{
	namespace content
	{
		namespace view
		{
			namespace admin
			{
				class base:
					public n33100::base
				{
				public:
					/// init
					//virtual void				init_bc( jess::shared_ptr<box_client::content::scene::admin::base> );
					/// init
					virtual void				init( jess::shared_ptr<n32100::base> );
				};
			}
		}
	}
}

#endif
