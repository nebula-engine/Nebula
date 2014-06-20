//#include <Nebula/network/message.hh>

#include <Nebula/app/Base.hh>
#include <Nebula/core/actor/Base.hh>

#include <Nebula/message/Actor/Event/Base.hh>
#include <Nebula/core/actor/RigidStatic/remote.hpp>
#include <Nebula/core/scene/Remote.hh>

void		neb::core::scene::remote::step(neb::core::TimeStep const & ts) {
	neb::core::scene::base::step(ts);
}
sp::weak_ptr<neb::core::actor::rigidstatic::base>	neb::core::scene::remote::createActorRigidStaticUninitialized() {
	
	auto self(isSceneRemote());
	assert(self);
	
	auto actor(sp::make_shared<neb::core::actor::rigidstatic::remote>(self));

	neb::core::actor::util::parent::insert(actor);

	return actor;
}


