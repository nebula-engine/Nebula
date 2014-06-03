#ifndef NEBULA_NETWORK_SERVER_HPP
#define NEBULA_NETWORK_SERVER_HPP

#include <Galaxy-Network/server.hpp>

#include <Nebula/Network/communicating.hh>

namespace Neb {
	namespace Network {
		class Server: public gal::net::server {
			public:
				/** @brief ctor
*
				 * @param io_service boost asio io service
				 */
				Server(
						boost::asio::io_service& io_service,
						ip::tcp::endpoint const & endpoint);
				void			callback_accept(ip::tcp::socket&& socket);
				void			send_all(sp::shared_ptr<gal::net::omessage> omessage);
			private:
				std::vector< sp::shared_ptr< Neb::Network::Communicating > >	clients_;

		};
	}
}

#endif



