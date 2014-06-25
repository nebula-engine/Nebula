//#include <neb/network/message.hh>

//#include <neb/app/Base.hh>
#include <neb/core/actor/Base.hh>

#include <neb/message/Actor/Event/Base.hh>
#include <neb/core/actor/RigidStatic/remote.hpp>
#include <neb/core/scene/Remote.hh>

void		neb::core::scene::remote::step(gal::std::timestep const & ts) {
	neb::core::scene::base::step(ts);
}
sp::weak_ptr<neb::core::actor::rigidstatic::base>	neb::core::scene::remote::createActorRigidStaticUninitialized() {
	
	auto self(isSceneRemote());
	assert(self);
	
	auto actor(sp::make_shared<neb::core::actor::rigidstatic::remote>(self));

	neb::core::actor::util::parent::insert(actor);

	return actor;
}


