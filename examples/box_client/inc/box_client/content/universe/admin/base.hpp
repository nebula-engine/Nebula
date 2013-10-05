#ifndef __BOX_CLIENT_CONTENT_UNIVERSE_ADMIN_BASE__
#define __BOX_CLIENT_CONTENT_UNIVERSE_ADMIN_BASE__

#include <nebula/content/universe/admin/base.hpp>

namespace box_client
{
	namespace content
	{
		namespace universe
		{
			namespace admin
			{
				class base:
					public ncua::base
				{
				public:
					virtual void							init( boost::shared_ptr<nc::base>& );
				};
			}
		}
	}
}

#endif
