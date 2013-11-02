#ifndef __NEBULA_CONTENT_SHAPE_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_SHAPE_PHYSICS_BASE_HPP__

#include <memory>

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>


#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace shape
		{
			namespace physics
			{
				class base
				{
					public:
						/** \brief ctor
						 */
						base( std::shared_ptr<n35100::base> );
						/** \brief dtor
						 */
						virtual ~base();
						virtual void						init();
						virtual void						shutdown();
						std::weak_ptr<n35100::base>				parent_;
						physx::PxShape*						px_shape_;
				};
			}
		}
	}
}

#endif
