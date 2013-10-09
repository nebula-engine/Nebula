#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_MATERIAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_MATERIAL_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>
#include <nebula/utilities/types/content/actor/types.hpp>

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
					material();
					virtual void						init( jess::shared_ptr<nebula::content::actor::admin::material> );
					virtual void						shutdown();
					std::weak_ptr<ncaa::material>				parent_;
				};
			}
		}
	}
}




#endif

