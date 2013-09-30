#ifndef __NEBULA_CONTENT_VIEW_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_VIEW_ADMIN_BASE_HPP__

namespace nebula
{
	namespace content
	{
		namespace view
		{
			namespace admin
			{
				class base
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

#endif

