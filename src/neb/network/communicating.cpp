#include <neb/config.h>
#include <neb/app.h>
#include <neb/scene/scene.h>
#include <neb/network/communicating.h>

neb::network::communicating::communicating(neb::app_s app, int socket):
	gal::network::communicating(socket),
	app_(app)
{

}
void neb::network::communicating::process(gal::network::message::shared_t msg) {
	NEBULA_DEBUG_1_FUNCTION;
	
	assert(!app_.expired());
	auto app = app_.lock();
	
	int type;
	
	msg->read(&type, sizeof(int));
	
	switch(type)
	{
		default:
			break;
	}

}





