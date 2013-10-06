#ifndef __NEBULA_PLATFORM_PLATFORM_BASE_HPP__
#define __NEBULA_PLATFORM_PLATFORM_BASE_HPP__

#include <jess/shared_ptr.hpp>

#include <jess/shared_ptr.hpp>
#include <jess/map.hpp>

#include <nebula/utilities/types/framework/types.hpp>
#include <nebula/utilities/types/platform/types.hpp>
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
				public jess::enable_shared_from_this<npp::base>,
				public na::mailbox
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
				virtual void								init( const jess::shared_ptr<nf::app>& );
				/// shutdown
				virtual void								shutdown();
				/// update
				virtual void								update();
				/// request window
				virtual void								request_window( jess::shared_ptr<npw::base>& );
				/// create window
				virtual void								create_window( jess::shared_ptr<npw::base>& );
				/// delete window
				virtual void								delete_window( int );
				/// process event
				virtual void								process_event( int );
				/// process message
				virtual void								process_message( jess::shared_ptr<na::message> );
				/// parent
				std::weak_ptr<nf::app>						parent_;
				/// window
				jess::map<npw::base>							windows_;
				/// key down event map
				std::map<int,int>							key_down_event_;
			};
		}
	}
}

#endif
