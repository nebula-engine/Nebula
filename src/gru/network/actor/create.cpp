
#include <gru/actor/addr.hpp>
#include <gru/actor/actor.hpp>
#include <gru/network/message.hpp>

void glutpp::network::actor::create::load(glutpp::actor::actor_s actor) {
	assert(actor);
	
	get_addr()->load_parent(actor);
	get_desc()->load(actor);
	
}










