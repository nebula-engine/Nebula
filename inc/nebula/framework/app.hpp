#ifndef __NEBULA_FRAMEWORK_APP_HPP__
#define __NEBULA_FRAMEWORK_APP_HPP__

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>

#include <jess/shared_ptr.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace framework
	{
		/// boost asio ioservice
		/**
		 * The ioservice is global so that any object can access it directly.
		 * \todo move definition to new file
		 */
		extern boost::asio::io_service						g_io_;


		/// %app
		class app:
			public jess::enable_shared_from_this<n10000::app>
		{
		public:
			/// ctor
			app();
			/// dtor
			virtual ~app();
			/// init
			virtual void						init();
			/// shutdown
			virtual void						shutdown();
			/// main loop sequ
			void							MainLoopSequ();
			/// main loop multi
			void							MainLoopMulti();
			/// continue sequ
			void							ContinueLoopSequ();
			/// continue multi
			void							ContinueLoopMulti();
			/// request_window
			virtual jess::shared_ptr<n22000::base>			request_window();
			/// get content
			jess::shared_ptr<nebula::content::base>			get_content();
			/// get platform
			jess::shared_ptr<n21000::base>				get_platform();
			///@name children
			///@{
			/// contnt
			jess::shared_ptr<n30000::base>				content_;
			/// platform
			jess::shared_ptr<n21000::base>				platform_;
			/// renderable
			jess::shared_ptr<n10000::renderable>			renderable_;
			///@}

		};
	}
}

#endif

