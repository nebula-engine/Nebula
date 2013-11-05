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
				UNIVERSE	= 0x4000,
				SCENE		= 0X4001,
				VIEW		= 0X4002,
			};
		}
	}
}

#endif

