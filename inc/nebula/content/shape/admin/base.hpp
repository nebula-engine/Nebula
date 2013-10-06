#ifndef __NEBULA_CONTENT_SHAPE_ADMIN_BASE_HPP__
#define __NEBULA_CONTENT_SHAPE_ADMIN_BASE_HPP__

#include <boost/numeric/ublas/vector.hpp>

#include <jess/shared_ptr.hpp>

#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/actor/types.hpp>
#include <nebula/utilities/types/content/shape/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace admin
			{
				class base:
					public jess::enable_shared_from_this<ncsa::base>
				{
				public:
					base();
					virtual ~base();
					
					/// init
					virtual void							init( jess::shared_ptr<nebula::content::actor::admin::rigid_actor>& );
					/// shutdown
					virtual void							shutdown();
					/// render
					virtual void							render( jess::shared_ptr<nebula::platform::renderer::base>& );
					
					
					/// get scale
					boost::numeric::ublas::vector<FLOAT>				get_scale();

					
					/// parent
					std::weak_ptr<nebula::content::actor::admin::rigid_actor>	parent_;
		
					/// renderer
					jess::shared_ptr<nebula::content::shape::renderer::base>	renderer_;
					/// physics
					jess::shared_ptr<nebula::content::shape::physics::base>		physics_;

					/// scale
					boost::numeric::ublas::vector<FLOAT>				scale_;
				};
			}
		}
	}
}


#endif
