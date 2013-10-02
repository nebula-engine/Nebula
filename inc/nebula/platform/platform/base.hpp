#ifndef __NEBULA_PLATFORM_PLATFORM_BASE_HPP__
#define __NEBULA_PLATFORM_PLATFORM_BASE_HPP__

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

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
			class base:
				public boost::enable_shared_from_this<npp::base>,
				public na::mailbox
			{
			public:
				struct event
				{
					enum
					{
						eDELETE_WINDOW
					};
				};
				base();
				virtual ~base();

				virtual void								init( const boost::shared_ptr<nf::app>& );
				virtual void								shutdown();
				virtual void								update();
				virtual void								create_window( boost::shared_ptr<npw::base>& );
				virtual void								delete_window( int );
				virtual void								process_event( int );
				virtual void								process_message( boost::shared_ptr<na::message> );
				boost::weak_ptr<nf::app>						parent_;

				jess::map<npw::base>							windows_;

				std::map<int,int>							key_down_event_;

			};
		}
	}
}

#endif
