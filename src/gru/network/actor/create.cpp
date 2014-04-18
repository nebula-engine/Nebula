#include <glutpp/network/message.h>

#include <glutpp/actor/addr.h>
#include <glutpp/actor/actor.h>

void glutpp::network::actor::create::load(glutpp::actor::actor_s actor) {
	assert(actor);
	
	get_addr()->load_parent(actor);
	get_desc()->load(actor);
	
}










