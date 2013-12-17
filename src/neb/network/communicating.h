#ifndef __NEBULA_ASIO_NETWORK_COMMUNICATING_H__
#define __NEBULA_ASIO_NETWORK_COMMUNICATING_H__

#include <gal/network/communicating.h>

namespace neb
{
	namespace network
	{
		class communicating: virtual public gal::network::communicating
		{
			public:
				void	process(gal::network::message::shared_t);
		};
	}
}

#endif
