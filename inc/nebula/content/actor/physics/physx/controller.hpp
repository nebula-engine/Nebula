#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_CONTROLLER_HPP__

#include <nebula/content/actor/physics/controller.hpp>
#include <nebula/content/actor/physics/physx/base.hpp>

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
					/// controller
					class controller:
						virtual public nebula::content::actor::physics::controller,
						virtual public nebula::content::actor::physics::physx::base
					{
						public:
							///@name ctor and dtor
							///@{
							// Ctor
							controller();
							/// Copy Ctor
							controller(const controller&);
							/// Dtor
							~controller();
							///@}

							///@name operator
							///@{
							/// assignment
							controller&								operator=(const controller&);
							///@}



							/// init
							virtual	void								init( jess::shared_ptr<ncaa::base> );
							/// shutdown
							virtual	void								shutdown();
							/// update
							virtual	void								update();
							/// step
							virtual	void								step(FLOAT);
							/// render
							virtual	void								render( jess::shared_ptr<npr::base> );




							/// create shapes
							virtual	void								create_shape();

							::physx::PxController*							get_px_controller();
							void									set_px_controller( ::physx::PxController* );

							/// PxController
							::physx::PxController*							px_controller_;
					};
				}
			}
		}
	}
}

#endif








