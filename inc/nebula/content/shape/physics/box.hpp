#ifndef __NEBULA_CONTENT_SHAPE_PHYSICS_BOX_HPP__
#define __NEBULA_CONTENT_SHAPE_PHYSICS_BOX_HPP__

#include <nebula/utilities/types/content/shape/types.hpp>

#include <nebula/content/shape/physics/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace physics
			{
				class box:
					public ncsp::base
				{
				public:
					box();
					~box();
					void						init( jess::shared_ptr<ncsa::base> );
					void						shutdown();
				};
			}
		}
	}
}


#endif
