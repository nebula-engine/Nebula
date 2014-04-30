#ifndef __JESS_ASIO_NETWORK_SOCKET_CLIENT_HPP__
#define __JESS_ASIO_NETWORK_SOCKET_CLIENT_HPP__

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>

#include <gru/network/communicating.hpp>

//typedef std::shared_ptr<boost::asio::io_service>	boost_io_service_ptr;

namespace gal {
	namespace network {
		/// socket_client
		class client: virtual public gal::network::communicating {
			public:
				/// shared_ptr
				typedef std::shared_ptr<client>	shared_t;

				/// ctor
				client(char const * address, unsigned short port);

				/// write
				//void	write(gal::asio::message::shared_t msg);
				/// close
				//void	close();

			private:
				/// do_connect
				//void	do_connect();
				/// handle_do_connect
				//void	handle_do_connect();

				char const *	foreign_address_;
				unsigned short	foreign_port_;
		};
	}
}


#endif // __JESS_ASIO_NETWORK_SOCKET_CLIENT_HPP__






