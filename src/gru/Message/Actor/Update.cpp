#include <gru/actor/addr.hpp>
#include <gru/actor/actor.hpp>
#include <gru/Message/Actor/Update.hpp>

void glutpp::network::actor::update::load(Neb::weak_ptr<glutpp::actor::actor> const & actor) {
	//assert(actor);
	
	/** @todo this and all similar functions should be not be called "load", in fact, they are used on the "save" 
	 * side of the serialization process. if anything, call them save.
	 */
	 
	//glutpp::network::actor::vec_addr_raw::tuple t;
	
	//gal::reset_tuple(t);

	boost::shared_ptr<glutpp::network::actor::update::addr_raw> ar(new glutpp::network::actor::update::addr_raw);
	
	ar->addr_.load_this(actor);
	
	ar->raw_ = actor->raw_;
	
	if(actor->any(glutpp::actor::actor::flag::SHOULD_UPDATE)) {
		vector_.push_back(ar);
	}
	
	// children
	for(auto it = actor->actors_.map_.cbegin(); it != actor->actors_.map_.cend(); ++it) {
		load(it->second);
	}
}





