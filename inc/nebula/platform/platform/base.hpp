#ifndef __NEBULA_PLATFORM_PLATFORM_BASE_HPP__
#define __NEBULA_PLATFORM_PLATFORM_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <jess/shared_ptr.hpp>
#include <jess/map.hpp>

#include <nebula/asio/mailbox.hpp>
#include <nebula/ns.hpp>

namespace nebula
{
	namespace platform
	{
		namespace platform
		{
			/// base
			class base:
				public jess::enable_shared_from_this<n21000::base>,
				public n40000::mailbox
			{
			public:
				/// event
				struct event
				{
					/// enum
					enum
					{
						eDELETE_WINDOW
					};
				};
				/// ctor
				base();
				/// dtor
				virtual ~base();
				/// init
				virtual void								init( jess::shared_ptr<n10000::app> );
				/// shutdown
				virtual void								shutdown();
				/// update
				virtual void								update();
				/// request window
				virtual jess::shared_ptr<n22000::base>					request_window();
				/// create window
				virtual jess::shared_ptr<n22000::base>					create_window();
				/// delete window
				virtual void								delete_window( int );
				/// process event
				virtual void								process_event( int );
				/// process message
				virtual void								process_message( jess::shared_ptr<n40000::message> );
				/// parent
				std::weak_ptr<n10000::app>						parent_;
				/// window
				jess::map<n22000::base>							windows_;
				/// key down event map
				std::map<int,int>							key_down_event_;
			};
		}
	}
}

#endif
