#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/Util/Cast.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>


Neb::Actor::Base_s				Neb::Actor::Util::Cast::isActorBase() {
        return std::dynamic_pointer_cast<Neb::Actor::Base>(shared_from_this());
}
Neb::Actor::Actor::Base_s			Neb::Actor::Util::Cast::isActorActor() {
	return std::dynamic_pointer_cast<Neb::Actor::Actor::Base>(shared_from_this());
}
Neb::Actor::RigidActor::Base_s			Neb::Actor::Util::Cast::isActorRigidActor() {
	return std::dynamic_pointer_cast<Neb::Actor::RigidActor::Base>(shared_from_this());
}
Neb::Actor::RigidBody::Base_s			Neb::Actor::Util::Cast::isActorRigidBody() {
	return std::dynamic_pointer_cast<Neb::Actor::RigidBody::Base>(shared_from_this());
}
