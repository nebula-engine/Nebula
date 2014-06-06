#include <Galaxy-Network/message.hpp>


#include <Nebula/log.hh>
#include <Nebula/config.hh>
#include <Nebula/Actor/Base.hh>
#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Message/Base.hh>
#include <Nebula/Network/communicating.hh>

Neb::Network::Communicating::Communicating(boost::asio::io_service& io_service, ip::tcp::socket&& socket):
	gal::net::communicating(io_service, std::move(socket))
{}
Neb::Network::Communicating::Communicating(boost::asio::io_service& io_service):
	gal::net::communicating(io_service)
{}
void		Neb::Network::Communicating::process(sp::shared_ptr<gal::net::imessage> buffer) {
	BOOST_LOG_CHANNEL_SEV(lg, "Neb::Network", debug) << __PRETTY_FUNCTION__;

	gal::std::wrapper<Neb::Message::IBase>	wrapper;

	buffer->ar_ >> wrapper;
}





