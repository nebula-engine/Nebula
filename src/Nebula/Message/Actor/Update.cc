#include <Nebula/actor/addr.hpp>
#include <Nebula/actor/actor.hpp>
#include <Nebula/Message/Actor/Update.hpp>

Neb::Message::Actor::OUpdate&		Neb::Message::Actor::OUpdate::operator<<(Neb::Actor::Base_s actor) {
	count_++;
	actor->serialize(*this, 0);
}



Neb::Message::Actor::IUpdate&		Neb::Message::Actor::IUpdate::operator>>(Neb::Scene::Base_s scene) {
	msg_->ar_ >> count_;

	Neb::Actor::Util::Address address;
	Neb::Actor::Base_s actor;
	for(int i = 0; i < count_; ++i) {
		msg_->ar_ >> address;

		actor = scene->getActor(address);
		assert(actor);

		msg_->ar_ >> *actor;
	}
	actor->serialize(*this, 0);
}





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





