#include <neb/config.h>
#include <neb/app.h>
#include <neb/scene/scene.h>
#include <neb/packet/packet.h>
#include <neb/network/communicating.h>

neb::network::communicating::communicating(neb::app_shared app, int socket):
	gal::network::communicating(socket),
	app_(app)
{

}
void neb::network::communicating::process(gal::network::message::shared_t message) {
	NEBULA_DEBUG_1_FUNCTION;

	//abort();

	assert(!app_.expired());

	auto app = app_.lock();
	std::shared_ptr<neb::scene::scene> scene;

	neb::packet::packet p;

	memcpy(&p, message->body(), message->body_length());

	switch(p.type)
	{
		default:
			break;
	}

}


