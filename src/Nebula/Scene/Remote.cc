//#include <Nebula/network/message.hh>

#include <Nebula/App/Base.hh>
#include <Nebula/Actor/Base.hh>

#include <Nebula/Message/Actor/Event/Base.hh>
#include <Nebula/Actor/RigidStatic/remote.hpp>
#include <Nebula/Scene/Remote.hh>

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


