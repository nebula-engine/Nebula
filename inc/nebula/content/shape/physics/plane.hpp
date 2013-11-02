#ifndef __NEBULA_CONTENT_SHAPE_PHYSICS_PLANE_HPP__
#define __NEBULA_CONTENT_SHAPE_PHYSICS_PLANE_HPP__

#include <nebula/content/shape/physics/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace physics
			{
				class plane:
					public n35200::base
				{
					protected:
					public:
						/** \brief ctor
						 */
						plane( std::shared_ptr<n35100::base> );
						/** \brief dtor
						 */
						virtual ~plane();
						/** \brief init
						 */
						virtual void			init();
				};
			}
		}
	}
}

#endif
