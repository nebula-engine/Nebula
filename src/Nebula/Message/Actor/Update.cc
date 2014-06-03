#include <Galaxy-Standard/registry.hpp>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Message/Actor/Update.hh>


void					Neb::Message::Actor::IUpdate::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	gal::std::index_type i;
	sp::shared_ptr<Neb::Actor::Base> actor;
	
	size_t size;
	ar >> size;
	
	for(size_t a = 0; a < size; ++a) {
		ar >> i;
		actor = sp::dynamic_pointer_cast< Neb::Actor::Base >(gal::std::shared::registry_.get(i));
		ar >> *actor;
	}
}


void					Neb::Message::Actor::OUpdate::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
	size_t size = actors_.size();
	ar << size;
	
	for(auto it = actors_.cbegin(); it != actors_.cend(); ++it) {
		//sp::shared_ptr<Neb::Actor::Base> const & actor = *it;
		/** @todo why?!?!?!? */
		//ar << actor->i_;
		//ar << *actor;
	}
}

