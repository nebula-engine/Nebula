
#include <Nebula/Actor/Base.hh>
#include <Nebula/Message/Actor/Update.hh>


void					Neb::Message::Actor::IUpdate::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	Neb::Util::index_type i;
	Neb::Actor::Base_s actor;
	
	size_t size;
	ar >> size;
	
	for(size_t a = 0; a < size; ++a) {
		ar >> i;
		actor = std::dynamic_pointer_cast<Neb::Actor::Base>(Neb::Util::Shared::registry_.get(i));
		ar >> *actor;
	}
}


void					Neb::Message::Actor::OUpdate::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
	size_t size = actors_.size();
	ar << size;

	for(auto it = actors_.cbegin(); it != actors_.cend(); ++it) {
		auto actor = *it;
		ar << actor->i_;
		ar << *actor;
	}
}









