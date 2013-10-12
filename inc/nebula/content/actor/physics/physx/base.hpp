#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/content/actor/physics/base.hpp>

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
					/// rigid dynamic
					class base:
						virtual public n34200::base
					{
						public:
							///@name ctor and dtor
							///@{
							// Ctor
							base();
							/// Copy Ctor
							base(const base&);
							/// Dtor
							~base();
							///@}

							///@name operator
							///@{
							/// assignment
							base&									operator=(const base&);
							///@}



							/// init
							virtual	void								init( jess::shared_ptr<nebula::content::actor::admin::base> );
							/// shutdown
							virtual	void								shutdown();
							/// update
							virtual	void								update();
							/// step
							virtual	void								step(float);
							/// render
							virtual	void								render( jess::shared_ptr<nebula::platform::renderer::base> );




							/// create shapes
							virtual	void								create_shape();


					};
				}
			}
		}
	}
}


#endif








