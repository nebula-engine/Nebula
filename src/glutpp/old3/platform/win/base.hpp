#include <memory>
#include <map>

#include <nebula/platform/platform/base.hpp>

namespace nebula
{
	namespace platform
	{
		namespace platform
		{
			namespace win
			{
				/// %Platform
				class base:
					public n21000::base
				{
					public:
						/** ctor
						*/
						base();
						/** dtor
						*/
						~base();
						/** init
						*/
						void					init();
						/** shutdown
						*/
						void					shutdown();
						/** update
						*/
						void					update();
						/** window
						*/
						jess::shared_ptr<n22000::base>		create_window();
				};
			}
		}
	}
}



