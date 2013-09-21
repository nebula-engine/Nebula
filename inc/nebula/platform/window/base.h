#ifndef _PLATFORM_WINDOW_WINDOW_H
#define _PLATFORM_WINDOW_WINDOW_H

#include <memory>

#include <boost/signals2/signal.hpp>

#include <utilities/Types/Utilities.h>

#include <framework/FR_Mappable.h>
//#include <framework/Communication/FR_COM_IComm.h>

using namespace std;

namespace Platform {
	namespace Window {
		/// %Window
		class Window: public FR_Mappable
		{
		public:
			///@name Constructor and Destructor
			///@{
			/// Constructor
										Window();
			/// Destructor
			virtual						~Window();
			///@}



			///@name Initialization and ShutDown
			///@{
			/// initialize
			virtual	void				VInit( Void* data );
			/// shutdown
			virtual	void				VShutDown();
			/// update
			virtual void				VUpdate();
			///@}




			/// @name boost signals
			///{
			/// key down
			boost::signals2::signal<void (int,int)>		sig_key_down_;
			/// key up
			boost::signals2::signal<void (int,int)>		sig_key_up_;
			/// pointer motion
			boost::signals2::signal<void (int,int)>		sig_pointer_motion_;
			///}
		protected:
			/// focus
			bool				has_focus_;
			/// x
			int					center_x_;
			/// y
			int					center_y_;

		};
	}
}



#endif














