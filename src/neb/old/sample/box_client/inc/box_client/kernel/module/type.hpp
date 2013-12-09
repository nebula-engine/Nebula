#ifndef __BOX_KERNEL_MODULE_TYPE_HPP__
#define __BOX_KERNEL_MODULE_TYPE_HPP__

#include <stdint.h>

namespace box_client
{
	namespace kernel
	{
		namespace module
		{
			/** \brief type
			*/
			enum type: uint16_t
			{
				BC10000_APP	= 0x8000,
				BC31100_BASE	= 0x8001,
				BC32100_BASE	= 0X8002,
				BC33100_BASE	= 0X8003,
			};
		}
	}
}

#endif

