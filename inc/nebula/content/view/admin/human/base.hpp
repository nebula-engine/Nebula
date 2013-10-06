#ifndef __NEBULA_CONTENT_VIEW_ADMIN_HUMAN_BASE_HPP__
#define __NEBULA_CONTENT_VIEW_ADMIN_HUMAN_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/types.hpp>

#include <nebula/content/view/admin/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace view
		{
			namespace admin
			{
				namespace human
				{
					class base:
						public ncva::base
					{
					public:
						base();
						virtual ~base();
						virtual void					init( jess::shared_ptr<nc_sc_a::base>& );
						virtual void					shutdown();
						virtual void					update();
						virtual void					render();
						
						virtual void					create_camera();
						
						jess::shared_ptr<npw::base>			window_;
						
						jess::shared_ptr<nebula::content::camera>	camera_;
					};
				}
			}
		}
	}
}

#endif
