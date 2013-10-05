#ifndef __NEBULA_FRAMEWORK_APP_HPP__
#define __NEBULA_FRAMEWORK_APP_HPP__

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <jess/shared_ptr.hpp>

#include <nebula/utilities/types/framework/types.hpp>
#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace framework
	{
		/// app
		class app:
			public boost::enable_shared_from_this<nf::app>
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
			virtual void						request_window( jess::shared_ptr<npw::base>& );
			/// get content
			boost::shared_ptr<nebula::content::base>		get_content();
			/// get platform
			boost::shared_ptr<npp::base>				get_platform();
			///@name children
			///@{
			/// contnt
			jess::shared_ptr<nc::base>				content_;
			/// platform
			jess::shared_ptr<npp::base>				platform_;
			/// renderable
			jess::shared_ptr<nf::renderable>			renderable_;
			///@}
		};
	}
}

#endif

