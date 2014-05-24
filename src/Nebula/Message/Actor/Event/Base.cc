
#include <Nebula/Actor/Base.hh>

#include <Nebula/Message/Actor/Event/Base.hh>

/*
void		Neb::Message::Actor::Event::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
	ar & event_;
}
void		Neb::Message::Actor::Event::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	ar & event_;
}
*/
void		Neb::Message::Actor::Event::IFire::process() {

/*
	Neb::Message::Actor::Event actor_event;
	actor_event.read(msg);
*/

	auto actor = std::dynamic_pointer_cast<Neb::Actor::Base>(Neb::Util::Shared::registry_.get(i_));

	assert(actor);

	auto scene = actor->getScene();
	assert(scene);


	scene->fire(actor);
}







