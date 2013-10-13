#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>

#include <nebula/content/actor/physics/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// controller
				class controller:
					virtual public n34200::base
				{
					protected:
						/// copy ctor
						controller(const controller&);
						/// assignment
						controller&						operator=(const controller&);
					public:
						/// ctor
						controller( jess::shared_ptr<n34100::base> );
						/// dtor
						~controller();
						/// init
						virtual	void						init();
						/// shutdown
						virtual	void						shutdown();
						/// update
						virtual	void						update();
						/// step
						virtual	void						step(float);
						/// update move
						virtual void						update_move();
					public:
						/// px controller
						physx::PxController*					px_controller_;
						/// material
						jess::shared_ptr<n34200::material>			material_;
				};
			}
		}
	}
}

#endif








