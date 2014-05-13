
#include <gru/Message/Actor/Event.hpp>


void		Neb::Message::Actor::Event::serializeDerived(boost::archive::binary_oarchive & ar, unsigned int const & version) {
	ar & addr_;
	ar & event_;
}


