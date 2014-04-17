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
	msg->read(type);
	
	switch(type)
	{
		case glutpp::network::type::ACTOR_EVENT:
			printf("DEBUG: actor event message received\n");
			app->recv_actor_event(msg);
			break;
		case glutpp::network::type::CONTROL_UPDATE:
			printf("DEBUG: control update message received\n");
			app->recv_control_update(msg);
			break;
		default:
			printf("DEBUG: unknown message type %i\n", type);
			break;
	}

}





