#ifndef _CONTENT_PHYSICS_PHYSICS_H
#define _CONTENT_PHYSICS_PHYSICS_H

#include <memory>

#include <jess/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <nebula/utilities/types/content/types.hpp>
#include <nebula/utilities/types/content/scene/types.hpp>
#include <nebula/utilities/types/content/actor/types.hpp>

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
			virtual	void						init(const jess::shared_ptr<nebula::content::base>&);
			/// shutdown
			virtual	void						shutdown();
			///@}



			


			///@name Register objects
			///@{
			/// %CO_SC_AD_Scene
			virtual void						register_scene( const jess::shared_ptr<nc_sc_a::base>& );
			/// %Controller
			virtual	void						register_controller( const jess::shared_ptr<ncaa::controller>& );
			/// rigid dynamic
			virtual	void						register_rigid_dynamic( const jess::shared_ptr<ncaa::rigid_dynamic>& );
			///@}
			
			
			virtual void						add_actor( jess::shared_ptr<ncaa::base> );

		protected:
			/// parent
			std::weak_ptr<nebula::content::base>			parent_;
			
			
			
		};
	}
}
}

#endif









