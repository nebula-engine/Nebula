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
				/** \brief controller
				*/
				class controller:
					virtual public n34200::base
				{
					protected:
						/** \brief copy ctor
						*/
						controller( controller const & );
						/** \breef assignment
						*/
						controller&						operator=( controller const & );
						/** \brief ctor
						*/
						controller( n34100::base::shared_t );
					public:
						/** \brief dtor
						*/
						~controller();
						/** \brief init
						*/
						virtual	void						init();
						/** \brief shutdown
						*/
						virtual	void						shutdown();
						/**\brief/ update
						*/
						virtual	void						update();
						/** \brief step
						*/
						virtual	void						step( float );
					protected:
						/** \brief px controller
						*/
						physx::PxController*					px_controller_;
						/** \brief material
						*/
						n34200::material::shared_t				material_;
				};
			}
		}
	}
}

#endif








