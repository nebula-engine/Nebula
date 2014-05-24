
#include <Nebula/Actor/Base.hh>

#include <Nebula/Message/Actor/Event/Base.hh>

/*
void		Neb::Message::Actor::Event::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
	ar & event_;
}*/
void		Neb::Message::Actor::Event::IFire::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	Neb::Message::Actor::IBase::serialize(ar, version);
	
	auto actor = std::dynamic_pointer_cast<Neb::Actor::Base>(Neb::Util::Shared::registry_.get(index_));

	assert(actor);

	auto scene = actor->getScene();
	assert(scene);


	scene->fire(actor);
}







