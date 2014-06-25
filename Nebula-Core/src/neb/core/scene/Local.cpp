
//#include <neb/app/Base.hh>

#include <neb/core/scene/Local.hh>
#include <neb/core/actor/Base.hh>
#include <neb/core/actor/RigidBody/Base.hh>
#include <neb/core/actor/RigidStatic/local.hpp>
//#include <neb/timer/Actor/Release.hpp>

neb::core::scene::local::local(sp::shared_ptr<neb::core::scene::util::parent> parent):
	neb::core::scene::base(parent)
{
}
void		neb::core::scene::local::step(gal::std::timestep const & ts) {
	neb::core::scene::base::step(ts);
}
void neb::core::scene::local::send_actor_update() {
	//printf("DEBUG: message ACTOR_UPDATE sent\n");


	//int type = glutpp::network::type::ACTOR_UPDATE;
	//msg->write(&type, sizeof(int));
/*
	sp::shared_ptr<neb::message::actor::OUpdate> message(new neb::message::actor::OUpdate);

	typedef neb::core::actor::util::parent A;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<neb::core::actor::base>(it->ptr_);
			assert(actor);
			if(actor->flag_.any(neb::core::actor::util::flag::SHOULD_UPDATE)) {
			message->actors_.push_back(actor);
			}
			});


	neb::app::base::global()->sendServer(message);
*/
}
sp::weak_ptr<neb::core::actor::rigidstatic::base>	neb::core::scene::local::createActorRigidStaticUninitialized() {
	
	auto actor(sp::make_shared<neb::core::actor::rigidstatic::local>(isSceneLocal()));

	neb::core::actor::util::parent::insert(actor);

	return actor;
}




