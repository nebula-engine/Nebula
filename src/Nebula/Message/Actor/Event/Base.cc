
#include <Nebula/Message/Actor/Event/Base.hh>


void		Neb::Message::Actor::Event::serializeDerived(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
	ar & event_;
}
void		Neb::Message::Actor::Event::serializeDerived(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	ar & event_;
}

void		Neb::Message::Actor::Event::process()

	Neb::Message::Actor::Event actor_event;
	actor_event.read(msg);

	auto actor = get_actor(actor_event.get_addr());
	assert(actor);
	auto scene = actor->get_scene();
	assert(scene);

	int type = actor_event.get_event()->type_;

	switch(type)
	{
		case Neb::actor::event::type::e::FIRE:
			scene->fire(actor);
			break;
		default:
			printf("DEBUG: unknown event type %i\n", type);
			break;
	}
}

