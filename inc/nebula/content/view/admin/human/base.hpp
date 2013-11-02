#ifndef __NEBULA_CONTENT_VIEW_ADMIN_HUMAN_BASE_HPP__
#define __NEBULA_CONTENT_VIEW_ADMIN_HUMAN_BASE_HPP__


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
						public n33100::base
					{
						public:
							/// ctor
							base();
							/// dtor
							virtual ~base();
							/// init
							virtual void					init( std::shared_ptr<n32100::base> );

							virtual void					shutdown();

							virtual void					update();

							virtual void					render();

							virtual void					create_camera();
					};
				}
			}
		}
	}
}

#endif
