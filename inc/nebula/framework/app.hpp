#ifndef __NEBULA_FRAMEWORK_APP_HPP__
#define __NEBULA_FRAMEWORK_APP_HPP__

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <jess/shared_ptr.hpp>

#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace framework
	{
		class app:
			public boost::enable_shared_from_this<nf::app>
		{
		public:
			app();
			virtual ~app();
			

			virtual void						init();
			virtual void						shutdown();
			


			void							MainLoopSequ();
			void							MainLoopMulti();
			void							ContinueLoopSequ();
			void							ContinueLoopMulti();


			jess::shared_ptr<nc::base>				content_;
			jess::shared_ptr<npp::base>				platform_;
			
			
			boost::shared_ptr<nebula::content::base>		get_content();
			boost::shared_ptr<npp::base>				get_platform();


		};
	}
}

#endif
