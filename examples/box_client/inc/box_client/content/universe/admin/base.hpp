#ifndef __BOX_CLIENT_CONTENT_UNIVERSE_ADMIN_BASE__
#define __BOX_CLIENT_CONTENT_UNIVERSE_ADMIN_BASE__

#include <nebula/content/universe/admin/base.hpp>

#include <box_client/ns.hpp>

namespace box_client
{
	namespace content
	{
		namespace universe
		{
			namespace admin
			{
				class base:
					public n31100::base
				{
					public:	
						/// ctor
						base( std::shared_ptr<n30000::base> );
						/// init
						virtual void							init();
				};
			}
		}
	}
}

#endif
