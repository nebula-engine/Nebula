#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Local.hh>
#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/timer/Actor/Release.hpp>

neb::scene::local::local(sp::shared_ptr<neb::scene::util::parent> parent):
	neb::scene::base(parent)
{
}
void		neb::scene::local::step(neb::core::TimeStep const & ts) {
	neb::scene::base::step(ts);
}
void neb::scene::local::send_actor_update() {
	//printf("DEBUG: message ACTOR_UPDATE sent\n");


	//int type = glutpp::network::type::ACTOR_UPDATE;
	//msg->write(&type, sizeof(int));

	sp::shared_ptr<neb::message::actor::OUpdate> message(new neb::message::actor::OUpdate);

	typedef neb::core::actor::util::parent A;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<neb::core::actor::base>(it->ptr_);
			assert(actor);
			if(actor->flag_.any(neb::core::actor::util::Flag::SHOULD_UPDATE)) {
			message->actors_.push_back(actor);
			}
			});


	neb::app::base::global()->sendServer(message);
}





