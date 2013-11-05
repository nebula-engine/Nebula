#ifndef __NEBULA_KERNEL_MODULE_TYPE_HPP__
#define __NEBULA_KERNEL_MODULE_TYPE_HPP__

#include <stdint.h>

namespace nebula
{
	namespace kernel
	{
		namespace module
		{
			/** \brief type
			*/
			enum type: uint16_t
			{
				CONTENT = 0xF000,
			};
		}
	}
}

#endif

