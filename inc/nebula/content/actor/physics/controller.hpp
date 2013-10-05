#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__



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
					public ncap::base
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
					virtual	void								init( boost::shared_ptr<ncaa::base>& );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step(FLOAT);
				
					virtual void								update_move();
					
				
				};
			}
		}
	}
}

#endif








