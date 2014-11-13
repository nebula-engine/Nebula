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

#include <boost/asio.hpp>

#include <Galaxy-Standard/map.hpp>

#include <gal/net/basic.hpp>
#include <gal/net/communicating.hpp>

namespace ip = boost::asio::ip;

namespace gal {
	namespace net {
		template<typename COMM> class server: public gal::itf::shared {
			public:
				typedef std::shared_ptr<gal::net::communicating>		comm_type;
				typedef std::shared_ptr<gal::net::message>		mesg_type;
			public:
				server(
						boost::asio::io_service& io_service,
						const ip::tcp::endpoint& endpoint):
					io_service_(io_service),
					acceptor_(io_service, endpoint),
					socket_(io_service)
			{
				//do_accept();
			}
				virtual ~server() {
					acceptor_.cancel();
				}
				void		do_accept() {

					auto self(std::dynamic_pointer_cast<gal::net::server<COMM>>(shared_from_this()));

					acceptor_.async_accept(
							socket_,
							boost::bind(
								&gal::net::server<COMM>::thread_accept,
								self,
								_1
								)
							);

				}
				void		close() {
					acceptor_.cancel();
				}
				void		thread_accept(boost::system::error_code ec) {

					if(!ec) {	
						::std::cout << "accepted" << ::std::endl;
						callback_accept(::std::move(socket_));
					}
					do_accept();
				}
				void		callback_accept(ip::tcp::socket&& socket) {
					auto clie = sp::make_shared<COMM>(io_service_, ::std::move(socket));
					clie->init();
					clients_.insert(clie);
				}
				virtual void					accept(std::shared_ptr<COMM>) = 0;
				void						send_all(std::shared_ptr<gal::net::omessage> omessage) {
					for(auto c : clients_) {
						c.ptr_->write(omessage);
					}
				}
			protected:
				boost::asio::io_service&			io_service_;
			private:
				ip::tcp::acceptor				acceptor_;
				ip::tcp::socket					socket_;
			private:
				gal::stl::map<COMM>				clients_;
		};
	}
}




#endif



