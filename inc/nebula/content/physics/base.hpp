#ifndef _CONTENT_PHYSICS_PHYSICS_H
#define _CONTENT_PHYSICS_PHYSICS_H

#include <memory>

#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace physics
		{
			/// physics for app
			/*
			 * -custom functionality
			 *     -drag-lift
			 *
			 * -before buffer swap
			 *     -onTrigger
			 *     -onContact
			 *     -onConstraintBreak
			 * -after buffer swap
			 *     -onSleep
			 *     -onWake
			 * -callbacks that occur for all objects
			 *     -onConstraintBreak
			 *     -onSleep
			 *     -onWake
			 * -callbacks that only occur if filter shader callback flag is set
			 *     -onTrigger
			 *     -onContact
			 * 
			 * 
			 * 
			 * 
			 */
			class base
			{
				public:
					///@name Constructors and Destructors
					///@{
					/// Constructor
					base();
					/// Destructor
					~base();
					///@}



					///@name standard functions
					///@{
					/// initialize
					virtual	void						init( jess::shared_ptr<nebula::content::base> );
					/// shutdown
					virtual	void						shutdown();
					///@}

					///@name Register objects
					///@{
					/// scene
					virtual void						register_scene( jess::shared_ptr<nc_sc_a::base> );
					/// controller
					virtual	void						register_controller( jess::shared_ptr<ncaa::controller> );
					/// rigid dynamic
					virtual	void						register_rigid_dynamic( jess::shared_ptr<ncaa::rigid_dynamic> );
					///@}


					virtual void						add_actor( jess::shared_ptr<ncaa::base> );

				//protected:
					/// parent
					std::weak_ptr<nebula::content::base>			parent_;



			};
		}
	}
}

#endif









