#ifndef __NEBULA_NETWORK_CLIENT_H__
#define __NEBULA_NETWORK_CLIENT_H__

#include <Nebula/network/client.hpp>

#include <Nebula/network2/communicating.hpp>

namespace Neb {
	namespace network {
		class client: virtual public Neb::network::communicating, virtual public gal::network::client {
			public:
				client(char const *, unsigned short);
				void	process(gal::network::message_s);

		};
	}
}

#endif





