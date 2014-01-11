#include <gal/util.h>

#include <glutpp/network/message.h>

#include <glutpp/actor/actor.h>

void glutpp::network::actor::update::load(glutpp::actor::actor_s actor) {
	assert(actor);
	
	tuple t;
	gal::reset_tuple(t);
	
	std::get<1>(t)->load(actor);
	*std::get<0>(t) = actor->raw_;
	
	if(actor->any(glutpp::actor::actor::SHOULD_UPDATE))
	{
		std::get<0>(tup_)->vec_.push_back(t);
	}
	
	for(auto it = actor->actors_.begin(); it != actor->actors_.end(); ++it)
	{
		auto a = it->second;
		
		load(a);
	}
}



