#include <gal/util.h>

#include <glutpp/network/message.h>

#include <glutpp/actor/actor.h>

void glutpp::network::actor::update::load(glutpp::actor::actor_s actor) {
	assert(actor);
	
	glutpp::network::actor::vec_addr_raw::tuple t;
	
	gal::reset_tuple(t);
	
	auto addr = std::get<1>(t);
	auto raw = std::get<0>(t);
	
	assert(addr);
	assert(raw);
	
	addr->load_this(actor);
	*raw = *actor->get_raw();
	
	if(actor->any(glutpp::actor::actor::flag::SHOULD_UPDATE))
	{
		std::get<0>(tup_)->vec_.push_back(t);
	}
	
	for(auto it = actor->actors_.begin(); it != actor->actors_.end(); ++it)
	{
		auto a = it->second;
		
		load(a);
	}
}



