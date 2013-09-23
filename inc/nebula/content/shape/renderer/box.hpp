#ifndef __NEBULA_CONTENT_SHAPE_RENDERER_BOX_HPP__
#define __NEBULA_CONTENT_SHAPE_RENDERER_BOX_HPP__

#include <nebula/utilities/types/content/shape/types.hpp>

#include <nebula/content/shape/renderer/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace renderer
			{
				class box: public nebula::content::shape::renderer::base
				{
				public:
					void								init(const boost::shared_ptr<nebula::content::shape::admin::box>&);
					void								render(const boost::shared_ptr<nebula::platform::renderer::base>&);
				};
			}
		}
	}
}


#endif
