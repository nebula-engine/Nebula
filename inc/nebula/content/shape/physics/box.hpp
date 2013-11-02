#ifndef __NEBULA_CONTENT_SHAPE_PHYSICS_BOX_HPP__
#define __NEBULA_CONTENT_SHAPE_PHYSICS_BOX_HPP__

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
					public n35200::base
				{
				public:
					box( std::shared_ptr<n35100::base> );
					~box();
					void						init();
					void						shutdown();
					void						create_shape();
				};
			}
		}
	}
}


#endif
