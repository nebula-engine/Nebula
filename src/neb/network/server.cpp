#include <assert.h>

#include <neb/app.h>
#include <neb/network/server.h>

neb::network::server::server(unsigned short port, int len):
	gal::network::server(port, len)
{
}
void neb::network::server::callback_accept(int s)
{
	std::shared_ptr<neb::network::communicating> c(new neb::network::communicating(s));
	c->start();
	
	assert(!app_.expired());
	auto app = app_.lock();
	
	app->transmit_scenes(c);
	
	clients_.push_back(c);
}




