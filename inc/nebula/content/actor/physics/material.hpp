#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_MATERIAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_MATERIAL_HPP__

#include <boost/shared_ptr.hpp>

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
					virtual void						init(const boost::shared_ptr<nebula::content::actor::admin::material>&);
					virtual void						shutdown();
				};
			}
		}
	}
}




#endif

