#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/Util/Cast.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>


sp::shared_ptr<neb::Actor::Base>				neb::Actor::Util::Cast::isActorBase() {
        return std::dynamic_pointer_cast<neb::Actor::Base>(shared_from_this());
}
sp::shared_ptr<neb::Actor::Actor::Base>			neb::Actor::Util::Cast::isActorActor() {
	return std::dynamic_pointer_cast<neb::Actor::Actor::Base>(shared_from_this());
}
sp::shared_ptr<neb::Actor::RigidActor::Base>			neb::Actor::Util::Cast::isActorRigidActor() {
	return std::dynamic_pointer_cast<neb::Actor::RigidActor::Base>(shared_from_this());
}
sp::shared_ptr<neb::Actor::RigidBody::Base>			neb::Actor::Util::Cast::isActorRigidBody() {
	return std::dynamic_pointer_cast<neb::Actor::RigidBody::Base>(shared_from_this());
}
