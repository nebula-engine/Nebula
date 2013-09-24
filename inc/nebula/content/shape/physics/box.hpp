#ifndef __NEBULA_CONTENT_SHAPE_PHYSICS_BOX_HPP__
#define __NEBULA_CONTENT_SHAPE_PHYSICS_BOX_HPP__

#include <nebula/utilities/types/content/shape/types.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace physics
			{
				class box
				{
				public:
					box();
					~box();
					void						init(const boost::shared_ptr<nebula::content::shape::admin::box>&);
					void						shutdown();
				};
			}
		}
	}
}


#endif
