#ifndef __NEBULA_CONTENT_SHAPE_RENDERER_BASE_HPP__
#define __NEBULA_CONTENT_SHAPE_RENDERER_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/shape/types.hpp>
#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace renderer
			{
				class base
				{
				public:
					base();
					virtual ~base();
					
					virtual void								init( jess::shared_ptr<nebula::content::shape::admin::base> );

					virtual void								shutdown();
					


					virtual void								render( jess::shared_ptr<nebula::platform::renderer::base> );
					
					/// parent
					std::weak_ptr<nebula::content::shape::admin::base>			parent_;
				};
			}
		}
	}
}

#endif









