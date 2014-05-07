#ifndef __JESS_ASIO_NETWORK_SOCKET_SERVER_HPP__
#define __JESS_ASIO_NETWORK_SOCKET_SERVER_HPP__

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>

#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in

//#include <galaxy/config.hpp>
#include <gru/network/communicating.hpp>

//typedef std::shared_ptr<boost::asio::io_service>      boost_io_service_ptr;
//typedef std::shared_ptr<boost::asio::ip::tcp::socket> boost_socket_ptr;

namespace gal
{
	namespace network
	{
		class communicating;
		class server
		{
			public:
				typedef boost::shared_ptr<gal::network::communicating>	comm_t;
				typedef boost::shared_ptr<gal::network::message>	msg_t;
				
				server(unsigned short localPort, int queueLen);
				void			thread_accept();
				virtual void		callback_accept(int) = 0;
				void			write(msg_t);
				void			close();
			private:
				int					socket_;
				
				std::thread				thread_accept_;
				std::mutex				mutex_;

				unsigned short				local_port_;
			public:
				std::vector<comm_t>			clients_;
		};
	}
}




#endif



