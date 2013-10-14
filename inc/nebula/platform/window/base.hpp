#ifndef _PLATFORM_WINDOW_WINDOW_H
#define _PLATFORM_WINDOW_WINDOW_H

#include <map>
#include <memory>

#include <jess/signal/signal.hpp>
#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace platform
	{
		namespace window
		{
			/// base
			class base:
				public jess::enable_shared_from_this<n22000::base>
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
				
				std::weak_ptr<n21000::base>			parent_;
				
				int						no_;
				bool						m_hasFocus;

				
				std::map<int,int>				keys_;

				///@name signals
				///@{
				/// key down
				jess::signal::signal<int,int>			sig_key_down_;
				/// key up
				jess::signal::signal<int,int>			sig_key_up_;
				/// pointer motion
				jess::signal::signal<int,int>			sig_pointer_motion_;
				///@}
			//protected:
				unsigned int					width_;
				unsigned int					height_;
				/// focus
				bool						has_focus_;
				/// x
				int						center_x_;
				/// y
				int						center_y_;
			

				jess::shared_ptr<n23000::base>			renderer_;
			};
		}
	}
}


#endif














