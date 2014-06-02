#ifndef __NEBULA_NETWORK_CLIENT_H__
#define __NEBULA_NETWORK_CLIENT_H__

#include <Galaxy-Network/client.hpp>

#include <Nebula/network2/communicating.hh>

namespace Neb {
	namespace Network {
		class Client:
			virtual public Neb::Network::Communicating,
			virtual public gal::network::client
		{
			public:
				Client(char const *, unsigned short);
				void	process(gal::network::message_s);

		};
	}
}

#endif





