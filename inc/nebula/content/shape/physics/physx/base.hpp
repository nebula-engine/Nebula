#ifndef __NEBULA_CONTENT_SHAPE_PHYSICS_PHYSX_BASE_HPP__
#define __NEBULA_CONTENT_SHAPE_PHYSICS_PHYSX_BASE_HPP__

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
				namespace physx
				{
					/// base
					class base
					{
						public:
							/// ctor
							base();
							/// dtor
							~base();
							/// init
							void						init( jess::shared_ptr<nebula::content::shape::admin::base> );
							/// shutdown
							void						shutdown();
					};
				}
			}
		}
	}
}


#endif


