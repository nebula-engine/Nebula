


#include <Nebula/App/Base.hh>
#include <Nebula/Actor/Base.hh>

#include <Nebula/Message/Actor/Event/Base.hh>

#include <Nebula/Scene/Remote.hh>

void neb::Scene::Remote::step(double const & time, double const & dt) {



}
void neb::Scene::Remote::fire(sp::shared_ptr<neb::Actor::Base> actor) {
	
	std::shared_ptr<neb::Message::Actor::Event::OFire> message(new neb::Message::Actor::Event::OFire);
	
	// fill message
	message->i_ = actor->i_;

	neb::App::Base::globalBase()->sendClient(message);
}

