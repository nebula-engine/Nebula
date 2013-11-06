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
				BC31100_BASE	= 0x4000,
				BC32100_BASE	= 0X4001,
				BC33100_BASE	= 0X4002,
			};
		}
	}
}

#endif

