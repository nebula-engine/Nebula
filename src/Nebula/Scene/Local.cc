#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Local.hh>
#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/timer/Actor/Release.hpp>

Neb::Scene::Local::Local(sp::shared_ptr<Neb::Scene::Util::Parent> parent):
	Neb::Scene::Base(parent)
{
}
void		Neb::Scene::Local::step(Neb::Core::TimeStep const & ts) {
	Neb::Scene::Base::step(ts);
}
void Neb::Scene::Local::send_actor_update() {
	//printf("DEBUG: message ACTOR_UPDATE sent\n");


	//int type = glutpp::network::type::ACTOR_UPDATE;
	//msg->write(&type, sizeof(int));

	Neb::Message::Actor::OUpdate_s message(new Neb::Message::Actor::OUpdate);

	typedef Neb::Actor::Util::Parent A;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<Neb::Actor::Base>(it->ptr_);
			assert(actor);
			if(actor->flag_.any(Neb::Actor::Util::Flag::SHOULD_UPDATE)) {
			message->actors_.push_back(actor);
			}
			});


	Neb::App::Base::globalBase()->sendServer(message);
}





