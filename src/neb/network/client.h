#ifndef __NEBULA_NETWORK_CLIENT_H__
#define __NEBULA_NETWORK_CLIENT_H__

#include <gal/network/client.h>

#include <neb/network/communicating.h>

namespace neb
{
        namespace network
        {
                class client: virtual public neb::network::communicating, virtual public gal::network::client
		{
			public:
				client(neb::app_s, char const *, unsigned short);
				void	process(gal::network::message::shared_t);
				
		};
        }
}

#endif





