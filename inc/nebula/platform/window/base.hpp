#ifndef _PLATFORM_WINDOW_WINDOW_H
#define _PLATFORM_WINDOW_WINDOW_H

#include <memory>

#include <boost/signals2/signal.hpp>

#include <jess/shared_ptr.hpp>

#include <nebula/utilities/types/platform/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace platform
	{
		namespace window
		{
			/// base
			class base:
				public jess::enable_shared_from_this<npw::base>
			{
			public:
				///@name Constructor and Destructor
				///@{
				/// Constructor
				base();
				/// Destructor
				virtual	~base();
				///@}
				
				
				
				///@name Initialization and ShutDown
				///{
				/// initialize
				virtual	void					init( jess::shared_ptr<nebula::platform::platform::base> );
				/// shutdown
				virtual	void					shutdown();
				/// update
				virtual void					update();
				///}
				
				virtual int					lookup_key( int );
				
				std::weak_ptr<npp::base>			parent_;
				
				int						no_;
				bool						m_hasFocus;

				
				std::map<int,int>				keys_;

				///@name boost signals
				///@{
				/// key down
				boost::signals2::signal<void (int,int)>		sig_key_down_;
				/// key up
				boost::signals2::signal<void (int,int)>		sig_key_up_;
				/// pointer motion
				boost::signals2::signal<void (int,int)>		sig_pointer_motion_;
				///@}
			//protected:
				/// focus
				bool						has_focus_;
				/// x
				int						center_x_;
				/// y
				int						center_y_;
			

				jess::shared_ptr<npr::base>			renderer_;
			};
		}
	}
}


#endif














