#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_MATERIAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_MATERIAL_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>


#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				class material
				{
					public:
						/** \brief ctor
						 */
						material();
						/** \brief init
						 */
						virtual void						init();
						virtual void						shutdown();

						physx::PxMaterial*					px_material_;
				};
			}
		}
	}
}




#endif

