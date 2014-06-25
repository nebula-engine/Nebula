#ifndef __NEBULA_NETWORK_CLIENT_H__
#define __NEBULA_NETWORK_CLIENT_H__

#include <Galaxy-Network/client.hpp>

#include <neb/net/communicating.hh>

namespace neb {
	namespace Network {
		class Client:
			virtual public neb::Network::Communicating,
			virtual public gal::net::client
		{
			public:
				Client(boost::asio::io_service& io_service, ip::tcp::resolver::iterator endpoint_iterator);
				void		process(sp::shared_ptr< gal::net::imessage > message);

		};
	}
}

#endif





