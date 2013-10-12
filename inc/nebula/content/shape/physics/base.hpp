#ifndef __NEBULA_CONTENT_SHAPE_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_SHAPE_PHYSICS_BASE_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>

#include <jess/shared_ptr.hpp>

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
						base();
						~base();
						void							init( jess::shared_ptr<nebula::content::shape::admin::base> );
						void							shutdown();
						std::weak_ptr<n35100::base>				parent_;
						physx::PxShape*						px_shape_;
				};
			}
		}
	}
}

#endif
