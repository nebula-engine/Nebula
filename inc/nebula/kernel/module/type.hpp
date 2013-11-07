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
				N10000_APP	= 0x4000,
				N22100_BASE	= 0x4001,
				N30000_BASE	= 0x4002,
				N30000_CAMERA	= 0x4003,
			};
		}
	}
}

#endif

