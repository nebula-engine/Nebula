#include <assert.h>

#include <neb/app.h>
#include <neb/network/server.h>

neb::network::server::server(neb::app_s app, unsigned short port, int len):
	gal::network::server(port, len),
	app_(app)
{
}
void neb::network::server::callback_accept(int s) {
	NEBULA_DEBUG_0_FUNCTION;
	
	assert(!app_.expired());
	auto app = app_.lock();

	std::shared_ptr<neb::network::communicating> c(new neb::network::communicating(app, s));
	c->start();
	
	app->transmit_scenes(c);
	
	clients_.push_back(c);
}




