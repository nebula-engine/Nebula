#include <Galaxy-Log/log.hpp>

#include <neb/debug.hh>
#include <neb/util/wrapper.hpp>
#include <neb/app/__net.hpp>

void neb::app::__net::reset_server(ip::tcp::endpoint const & endpoint) {
	//NEBULA_DEBUG_0_FUNCTION;
	server_.reset(new neb::Network::Server(ios_, endpoint));
}
void neb::app::__net::reset_client(ip::tcp::resolver::iterator endpoint_iterator) {
	//NEBULA_DEBUG_0_FUNCTION;
	client_.reset(new neb::Network::Client(ios_, endpoint_iterator));
}
void		neb::app::__net::sendServer(sp::shared_ptr< gal::net::omessage > msg)  {
	//NEBULA_DEBUG_1_FUNCTION;

	if(server_) {
		server_->write(msg);
	} else {
		if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb", debug) << "no server";
	}
}
void		neb::app::__net::sendClient(sp::shared_ptr< gal::net::omessage > msg)  {
	//NEBULA_DEBUG_1_FUNCTION;

	if(client_) {
		client_->write(msg);
	} else {
		if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb", debug) << "no client";
	}
}
void		neb::app::__net::sendClient(sp::shared_ptr< neb::message::OBase > message) {
	assert(message);
	
	/** @todo wtf */
	//neb::std::wrapper wrap(message);

	auto buffer = sp::make_shared<gal::net::omessage>();

	/** @todo boost serial warning */
	//buffer->ar_ << wrapper;

	sendClient(buffer);
}
void		neb::app::__net::sendServer(sp::shared_ptr< neb::message::OBase > message) {
	assert(message);

	/** @todo wtf */
	//neb::std::wrapper wrapper(message);

	auto buffer = sp::make_shared<gal::net::omessage>();

	/** @todo boost serial warning */
	//buffer->ar_ << wrapper;

	sendServer(buffer);
}






