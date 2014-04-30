
#include <gru/actor/addr.hpp>
#include <gru/actor/actor.hpp>
#include <gru/network/actor/Create.hpp>

void glutpp::network::actor::create::load(boost::shared_ptr<glutpp::actor::actor> actor) {
	assert(actor);
	
	addr_.load_parent(actor);

	desc_.load(actor);
	
}










