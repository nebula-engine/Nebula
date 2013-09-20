#ifndef __NEBULA_CONTENT_SHAPE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_SHAPE_ADMIN_BASE_HPP__

#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <nebula/shared_ptr.hpp>

#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/actor/types.hpp>
#include <nebula/utilities/types/content/shape/types.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace admin
			{
				class base
				{
				public:
					base();
					~base();
					
					/// init
					void								init(const boost::shared_ptr<nebula::content::actor::admin::rigid_actor>&);
					/// shutdown
					void								shutdown();
					/// render
					void								render(const boost::shared_ptr<nebula::platform::renderer::base>&);
					

					
					/// parent
					boost::weak_ptr<nebula::content::actor::admin::rigid_actor>	parent_;
		
					/// renderer
					nebula::shared_ptr<nebula::content::shape::renderer::base>	renderer_;
					/// physics
					nebula::shared_ptr<nebula::content::shape::physics::base>	physics_;
				};
			}
		}
	}
}


#endif
