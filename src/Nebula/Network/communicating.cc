#include <Galaxy-Network/message.hpp>

#include <Galaxy-Log/log.hpp>

//#include <Nebula/config.hh>
//#include <Nebula/App/Base.hh>
//#include <Nebula/Message/Base.hh>
#include <Nebula/Util/wrapper.hpp>
#include <Nebula/Network/communicating.hh>

Neb::Network::Communicating::Communicating(boost::asio::io_service& io_service, ip::tcp::socket&& socket):
	gal::net::communicating(io_service, std::move(socket))
{}
Neb::Network::Communicating::Communicating(boost::asio::io_service& io_service):
	gal::net::communicating(io_service)
{}
void		Neb::Network::Communicating::process(sp::shared_ptr<gal::net::imessage> buffer) {
	BOOST_LOG_CHANNEL_SEV(lg, "Neb::Network", debug) << __PRETTY_FUNCTION__;

	neb::std::wrapper/*<Neb::Message::IBase>*/	wrapper;

	buffer->ar_ >> wrapper;
}





