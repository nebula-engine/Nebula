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
						public ncva::base
					{
					public:
						virtual void					init( const boost::shared_ptr<nc_sc_a::base>& );
						virtual void					shutdown();
						virtual void					update();
					};
				}
			}
		}
	}
}

#endif
