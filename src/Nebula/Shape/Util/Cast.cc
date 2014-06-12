#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/Util/Cast.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>


sp::shared_ptr<neb::core::actor::Base>				neb::core::actor::Util::Cast::isActorBase() {
        return sp::dynamic_pointer_cast<neb::core::actor::Base>(shared_from_this());
}
sp::shared_ptr<neb::core::actor::actor::Base>			neb::core::actor::Util::Cast::isActorActor() {
	return sp::dynamic_pointer_cast<neb::core::actor::actor::Base>(shared_from_this());
}
sp::shared_ptr<neb::core::actor::RigidActor::Base>			neb::core::actor::Util::Cast::isActorRigidActor() {
	return sp::dynamic_pointer_cast<neb::core::actor::RigidActor::Base>(shared_from_this());
}
sp::shared_ptr<neb::core::actor::RigidBody::Base>			neb::core::actor::Util::Cast::isActorRigidBody() {
	return sp::dynamic_pointer_cast<neb::core::actor::RigidBody::Base>(shared_from_this());
}
