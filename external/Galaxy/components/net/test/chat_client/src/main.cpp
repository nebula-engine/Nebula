#include <iostream>

#include <gal/net/client.hpp>

namespace chat {
	class communicating: virtual public gal::net::communicating {
		public:
			communicating(boost::asio::io_service& io_service, ip::tcp::socket&& socket): gal::net::communicating(io_service, std::move(socket)) {}
			communicating(boost::asio::io_service& io_service): gal::net::communicating(io_service) {}
	};

	class client: virtual public gal::net::client, virtual public communicating {
		public:
			client(boost::asio::io_service& io_service, ip::tcp::resolver::iterator endpoint_iterator):
				gal::net::communicating(io_service),
				gal::net::client(io_service, endpoint_iterator),
				chat::communicating(io_service)
		{
		}

			void		process(std::shared_ptr<gal::net::imessage> message) {
				std::cout << "server: " << message->ss_.str() << std::endl;
			}
	};
}





int main(int ac, char** av) {

	if(ac != 3) {
		std::cout << "usage: " << av[0] << " <ip> <port>" << std::endl;
		return 1;
	}

	boost::asio::io_service io_service;

	ip::tcp::resolver resolver(io_service);
	auto endpoint_iterator = resolver.resolve({ av[1], av[2] });


	auto clie = std::make_shared<chat::client>(io_service, endpoint_iterator);

	std::thread t([&io_service](){ io_service.run(); });

	std::string text;
	while(1) {
		std::cin >> text;
		
		auto message = std::make_shared<gal::net::omessage>();
		
		message->ar_ << text;
		
		clie->write(message);
	}

	io_service.run();
}

