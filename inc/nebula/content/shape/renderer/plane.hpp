#ifndef __NEBULA_CONTENT_SHAPE_RENDERER_PLANE_HPP__
#define __NEBULA_CONTENT_SHAPE_RENDERER_PLANE_HPP__

#include <nebula/content/shape/renderer/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace renderer
			{
				/// %plane
				class plane:
					public n35300::base
				{
					public:
						/// ctor
						plane( jess::shared_ptr<n35100::base> );
						/// dtor
						virtual ~plane();
						/// init
						virtual void			init();
						/// shutdown
						virtual void			shutdown();
						/// render
						virtual void			render( jess::shared_ptr<n23000::base> );
				};
			}
		}
	}
}

#endif
