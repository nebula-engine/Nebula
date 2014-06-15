


#include <Nebula/App/Base.hh>
#include <Nebula/Actor/Base.hh>

#include <PhysX/message/actor/event/Base.hh>

#include <PhysX/core/scene/Remote.hh>

void		phx::core::scene::remote::step(neb::core::TimeStep const & ts) {



}
void		phx::core::scene::remote::fire(sp::shared_ptr<neb::core::actor::base> actor) {
	
	auto message(sp::make_shared< phx::message::actor::event::OFire >());
	
	// fill message
	message->i_ = actor->i_;

	neb::App::base::global()->sendClient(message);
}

