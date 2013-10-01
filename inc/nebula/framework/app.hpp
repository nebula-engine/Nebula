#ifndef __NEBULA_FRAMEWORK_APP_HPP__
#define __NEBULA_FRAMEWORK_APP_HPP__

#include <boost/shared_ptr.hpp>

#include <nebula/utilities/types/platform/types.hpp>
#include <nebula/utilities/types/content/types.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace framework
	{
		class app
		{
			public:





			boost::shared_ptr<nebula::content::base>		content_;
			boost::shared_ptr<npp::base>				platform_;


			boost::shared_ptr<nebula::content::base>		get_content();
			boost::shared_ptr<npp::base>				get_platform();


		};
	}
}

#endif
