#include <iostream>

#include <gal/net/server.hpp>

namespace chat {
	class communicating: public gal::net::communicating {
		public:
			communicating(boost::asio::io_service& io_service, ip::tcp::socket&& socket): gal::net::communicating(io_service, std::move(socket)) {}

			void		process(std::shared_ptr<gal::net::imessage> message) {
				std::cout << "client: " << message->ss_.str() << std::endl;
			}
	};
	class server: public gal::net::server<chat::communicating> {
		public:
			server(boost::asio::io_service& io_service, ip::tcp::endpoint const & endpoint)
				: gal::net::server<chat::communicating>(io_service, endpoint) 
			{
			}
			virtual void		accept(std::shared_ptr<chat::communicating> client) {
			}
			
	};
}


int main(int ac, char** av) {

	if(ac != 2) {
		std::cout << "usage: " << av[0] << " <port>" << std::endl;
		return 1;
	}

	boost::asio::io_service io_service;

	ip::tcp::endpoint endpoint(ip::tcp::v4(), std::atoi(av[1]));

	auto serv = std::make_shared<chat::server>(io_service, endpoint);
	serv->do_accept();

	std::thread t([&io_service](){ io_service.run(); });

	std::string text;
	while(1) {
		std::cin >> text;
		
		std::cout << "sending '" << text << "'" << std::endl;
		
		auto message = std::make_shared<gal::net::omessage>();
		
		message->ar_ << text;

		serv->send_all(message);
	}

	io_service.run();
}

