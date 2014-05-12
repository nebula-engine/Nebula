#include <Nebula/Actor/Util/Cast.hh>

Neb::Actor::Base_s			Neb::Actor::Util::Cast::isActorBase() {
        return std::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());
}
Neb::Actor::Actor_s			Neb::Actor::Util::Cast::isActorActor() {
	return std::dynamic_pointer_cast<Neb::Actor::Actor>(shared_from_this());
}
Neb::Actor::RigidActor_s		Neb::Actor::Util::Cast::isActorRigidActor() {
	return std::dynamic_pointer_cast<Neb::Actor::RigidActor>(shared_from_this());
}
Neb::Actor::RigidBody::RigidBody_s	Neb::Actor::Util::Cast::isActorRigidBody() {
	return std::dynamic_pointer_cast<Neb::Actor::RigidBody::RigidBody>(shared_from_this());
}
