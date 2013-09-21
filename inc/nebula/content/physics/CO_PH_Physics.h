#ifndef _CONTENT_PHYSICS_PHYSICS_H
#define _CONTENT_PHYSICS_PHYSICS_H

#include <memory>

#include <utilities/Types/Utilities.h>

#include <content/Content.h>

using namespace std;

namespace Content {
	namespace Physics {
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
		class Physics {
		public:
			///@name Constructors and Destructors
			///@{
			/// Constructor
										Physics() {};
			/// Destructor
										~Physics() {};
			///@}

			

			///@name standard functions
			///@{
			/// initialize
			virtual	void				VInit( Void* data );
			/// shutdown
			virtual	void				VShutDown();
			///@}



			


			///@name Register objects
			///@{
			/// %CO_SC_AD_Scene
			virtual void				RegisterScene( CO_SC_AD_Scene* scene );
			/// %Controller
			virtual	void				RegisterController( CO_AC_AD_Controller*& controller, CO_SC_AD_Scene* scene );
			/// %RigidDynamic
			virtual	void				RegisterRigidDynamic( CO_AC_AD_RigidDynamic* rigidDynamic );
			///@}



		protected:
			/// centent
					::Content::Content*	m_parent;
		};
	};
};


#endif









