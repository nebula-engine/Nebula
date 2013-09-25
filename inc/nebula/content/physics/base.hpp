#ifndef _CONTENT_PHYSICS_PHYSICS_H
#define _CONTENT_PHYSICS_PHYSICS_H

#include <memory>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <nebula/utilities/types/content/types.hpp>

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
			virtual	void				init(const boost::shared_ptr<nebula::content::base>&);
			/// shutdown
			virtual	void				shutdown();
			///@}



			

/*
			///@name Register objects
			///@{
			/// %CO_SC_AD_Scene
			virtual void				RegisterScene(nebula::content CO_SC_AD_Scene* scene );
			/// %Controller
			virtual	void				RegisterController( CO_AC_AD_Controller*& controller, CO_SC_AD_Scene* scene );
			/// %RigidDynamic
			virtual	void				RegisterRigidDynamic( CO_AC_AD_RigidDynamic* rigidDynamic );
			///@}

*/

		protected:
			/// parent
			boost::weak_ptr<nebula::content::base>					parent_;
			
			
			
		};
	}
}
}

#endif









