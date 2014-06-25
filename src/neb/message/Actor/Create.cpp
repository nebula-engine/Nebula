
#include <neb/core/actor/Base.hh>

#include <neb/message/Actor/Create.hh>

void		neb::message::actor::Create::load(sp::shared_ptr<neb::core::actor::base> actor) {
	assert(actor);

	parent_i_ = actor->get_parent()->i_;
	
	i_ = actor->i_;
	
	wrapper_.ptr_ = actor;
}





