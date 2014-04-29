
//#include <galaxy/util.hpp>

#include <gru/network/message.hpp>

#include <gru/actor/addr.hpp>
#include <gru/actor/actor.hpp>

void glutpp::network::actor::update::load(boost::shared_ptr<glutpp::actor::actor> actor) {
	assert(actor);
	
	//glutpp::network::actor::vec_addr_raw::tuple t;
	
	//gal::reset_tuple(t);

	boost::shared_ptr<glutpp::network::actor::addr_raw> ar(new glutpp::network::actor::addr_raw);
	
	
	ar->addr_.load_this(actor);
	
	ar->raw_ = glutpp::master::Global()->actor_raw_factory_->create(actor->raw_->type_);
	
	ar->raw_->operator=(*(actor->raw_));
	
	if(actor->any(glutpp::actor::actor::flag::SHOULD_UPDATE))
	{
		vector_.push_back(ar);
	}
	
	for(auto it = actor->actors_.begin(); it != actor->actors_.end(); ++it)
	{
		auto a = it->second;
		
		load(a);
	}
}



