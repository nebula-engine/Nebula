
#include <Galaxy-Standard/registry.hpp>

#include <Nebula/Actor/Base.hh>

#include <Nebula/Message/Actor/Event/Base.hh>
#include <Nebula/Scene/Base.hh>


#include <PhysX/core/actor/Actor/base.hpp>
#include <PhysX/message/actor/event/Base.hh>

/*
void		neb::message::actor::Event::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
	ar & event_;
}*/
void		px::message::actor::event::IFire::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	neb::message::actor::IBase::serialize(ar, version);
	
	auto actor = sp::dynamic_pointer_cast<px::core::actor::actor::base>(gal::std::shared::registry_.get(index_));
	assert(actor);

	//auto scene = actor->getScene();
	//assert(scene);

	//scene->fire(actor);
	actor->fire();
}







