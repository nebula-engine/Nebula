#ifndef __JESS_ASIO_NETWORK_SOCKET_CLIENT_HPP__
#define __JESS_ASIO_NETWORK_SOCKET_CLIENT_HPP__

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>

#include <boost/asio.hpp>

#include <gal/net/communicating.hpp>

//typedef std::shared_ptr<boost::asio::io_service>	boost_io_service_ptr;

namespace gal {
	namespace net {
		/// socket_client
		class client: virtual public gal::net::communicating {
			public:
				/// std::shared_ptr
				typedef std::shared_ptr<client>	shared_t;

				/// ctor
				client(
						boost::asio::io_service& io_service,
						ip::tcp::resolver::iterator endpoint_iterator);


				/// write
				//void	write(gal::asio::message::shared_t msg);
				/// close
				//void	close();

			private:
				/// do_connect
				void	do_connect(ip::tcp::resolver::iterator endpoint_iterator);
				/// handle_do_connect
				//void	handle_do_connect();

				boost::asio::io_service& io_service_;
		};
	}
}


#endif // __JESS_ASIO_NETWORK_SOCKET_CLIENT_HPP__






