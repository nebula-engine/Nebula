#ifndef __NEBULA_CONTENT_SHAPE_RENDERER_BASE_HPP__
#define __NEBULA_CONTENT_SHAPE_RENDERER_BASE_HPP__

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
					void							render(const boost::shared_ptr<nebula::platform::renderer::base>&);
				};
			}
		}
	}
}

#endif

