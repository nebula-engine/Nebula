#include <glutpp/network/message.h>

#include <glutpp/actor/actor.h>

void glutpp::network::actor::create::load(glutpp::actor::actor_shared actor) {
	assert(actor);
	
	std::get<1>(tup_)->load(actor);
	
	std::get<0>(tup_)->load(actor);
	
}










