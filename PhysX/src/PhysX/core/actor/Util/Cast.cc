
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/Actor/Util/Cast.hh>

sp::shared_ptr<neb::core::actor::Base>			neb::core::actor::Util::Cast::isActorBase() {
        return std::dynamic_pointer_cast<neb::core::actor::Base>(shared_from_this());
}
sp::shared_ptr<neb::core::actor::actor::Base>		neb::core::actor::Util::Cast::isActorActor() {
	return std::dynamic_pointer_cast<neb::core::actor::actor::Base>(shared_from_this());
}
sp::shared_ptr<neb::core::actor::rigidactor::Base>		neb::core::actor::Util::Cast::isActorRigidActor() {
	return std::dynamic_pointer_cast<neb::core::actor::rigidactor::Base>(shared_from_this());
}
sp::shared_ptr<neb::core::actor::rigidbody::Base>		neb::core::actor::Util::Cast::isActorRigidBody() {
	return std::dynamic_pointer_cast<neb::core::actor::rigidbody::Base>(shared_from_this());
}
