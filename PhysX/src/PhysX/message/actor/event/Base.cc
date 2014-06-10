
#include <Galaxy-Standard/registry.hpp>

#include <Nebula/Actor/Base.hh>

#include <Nebula/Message/Actor/Event/Base.hh>
#include <Nebula/Scene/Base.hh>

/*
void		Neb::Message::Actor::Event::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
	ar & event_;
}*/
void		Neb::Message::Actor::Event::IFire::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	Neb::Message::Actor::IBase::serialize(ar, version);
	
	auto actor = sp::dynamic_pointer_cast<Neb::Actor::Base>(gal::std::shared::registry_.get(index_));

	assert(actor);

	auto scene = actor->getScene();
	assert(scene);

	scene->fire(actor);
}







