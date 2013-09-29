#ifndef __NEBULA_CONTENT_SHAPE_ADMIN_BOX_HPP__
#define __NEBULA_CONTENT_SHAPE_ADMIN_BOX_HPP__

#include <boost/enable_shared_from_this.hpp>

#include <nebula/content/shape/admin/base.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace admin
			{
				class box:
					public nebula::content::shape::admin::base
				{
				public:
					void								init( const boost::shared_ptr<ncaa::rigid_actor>& );
					void								shutdown();
					void								render( const boost::shared_ptr<nebula::platform::renderer::base>&);
				

					
					FLOAT								x_;
					FLOAT								y_;
					FLOAT								z_;
					
				};
			}
		}
	}
}


#endif
