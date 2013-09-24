#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_MATERIAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_MATERIAL_HPP__


#include <nebula/content/actor/physics/material.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				namespace physx
				{
					class material:
						public nebula::content::actor::physics::material
					{
					public:
						boost::shared_ptr< ::physx::PxMaterial>				px_material_;
					};
				}
			}
		}
	}
}


#endif
