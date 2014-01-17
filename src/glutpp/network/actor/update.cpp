#include <gal/util.h>

#include <glutpp/network/message.h>

#include <glutpp/actor/actor.h>

void glutpp::network::actor::update::load(glutpp::actor::actor_s actor) {
	assert(actor);
	
	glutpp::network::actor::vec_addr_raw::tuple t;
	
	gal::reset_tuple(t);
	
	auto addr = std::get<1>(t);
	auto raw = std::get<0>(t);
	
	addr->load_this(actor);
	*raw = actor->raw_;
	
	if(actor->any(glutpp::actor::flag::SHOULD_UPDATE))
	{
		std::get<0>(tup_)->vec_.push_back(t);
	}
	
	for(auto it = actor->actors_.begin(); it != actor->actors_.end(); ++it)
	{
		auto a = it->second;
		
		load(a);
	}
}



