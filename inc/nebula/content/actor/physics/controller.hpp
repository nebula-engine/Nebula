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
					public:
						friend class n36000::base;
						friend class n34100::controller::base;
					protected:
						/** \brief copy ctor
						 */
						controller( controller const & );
						/** \breef assignment
						 */
						controller&						operator=( controller const & );
						/** \brief ctor
						 */
						controller( std::shared_ptr<n34100::base> );
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
						std::shared_ptr<n34200::material>			material_;
				};
			}
		}
	}
}

#endif








