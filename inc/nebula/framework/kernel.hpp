#ifndef __NEBULA_FRAMEWORK_KERNEL_HPP__
#define __NEBULA_FRAMEWORK_KERNEL_HPP__

#include <nebula/framework/module_parent.hpp>

namespace nebula
{
	namespace framework
	{
		/** \brief kernel
		 */
		class kernel:
			public n10000::module_parent
		{
			protected:
				std::shared_ptr<n10000::module>			request_module(
						std::shared_ptr<n10000::module>,
						std::shared_ptr<n10000::module_desc> );
		};
	}
}

#endif
