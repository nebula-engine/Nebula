

#include <gal/net/message.hpp>

#include <gal/log/log.hpp>

//#include <neb/config.hh>
//#include <neb/app/Base.hh>
//#include <neb/message/Base.hh>
#include <neb/util/wrapper.hpp>
#include <neb/net/communicating.hh>
#include <neb/debug.hh>

neb::Network::Communicating::Communicating(boost::asio::io_service& io_service, ip::tcp::socket&& socket):
	gal::net::communicating(io_service, ::std::move(socket))
{}
neb::Network::Communicating::Communicating(boost::asio::io_service& io_service):
	gal::net::communicating(io_service)
{}
void		neb::Network::Communicating::process(std::shared_ptr<gal::net::imessage> buffer) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb::Network", debug) << __PRETTY_FUNCTION__;

	neb::stl::wrapper/*<neb::message::IBase>*/	wrapper;

	buffer->ar_ >> wrapper;
}





