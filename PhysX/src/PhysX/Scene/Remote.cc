#include <Nebula/network/message.hh>

#include <Nebula/App/Base.hh>
#include <Nebula/Actor/Base.hh>

#include <Nebula/Message/Actor/Event/Base.hh>

#include <Nebula/Scene/Remote.hh>

void Neb::Scene::Remote::step(double const & time, double const & dt) {



}
void Neb::Scene::Remote::fire(Neb::Actor::Base_s actor) {
	
	std::shared_ptr<Neb::Message::Actor::Event::OFire> message(new Neb::Message::Actor::Event::OFire);
	
	// fill message
	message->i_ = actor->i_;

	Neb::App::Base::globalBase()->sendClient(message);
}

