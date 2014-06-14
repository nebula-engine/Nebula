


#include <Nebula/App/Base.hh>
#include <Nebula/Actor/Base.hh>

#include <PhysX/message/actor/event/Base.hh>

#include <PhysX/core/scene/Remote.hh>

void		px::core::scene::remote::step(neb::core::TimeStep const & ts) {



}
void		px::core::scene::remote::fire(sp::shared_ptr<neb::core::actor::Base> actor) {
	
	auto message(sp::make_shared< px::message::actor::event::OFire >());
	
	// fill message
	message->i_ = actor->i_;

	neb::App::Base::global()->sendClient(message);
}

