
#include <Nebula/Actor/Base.hh>

#include <Nebula/Message/Actor/Create.hh>

void		Neb::Message::Actor::Create::load(Neb::Actor::Base_s actor) {
	assert(actor);

	parent_i_ = actor->parent_->i_;
	
	i_ = actor->i_;
	
	wrapper_.ptr_ = actor;
}





