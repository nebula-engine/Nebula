
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/Actor/Util/Cast.hh>

sp::shared_ptr<neb::core::actor::base>			neb::core::actor::util::Cast::isActorBase() {
        return std::dynamic_pointer_cast<neb::core::actor::base>(shared_from_this());
}
sp::shared_ptr<neb::core::actor::actor::base>		neb::core::actor::util::Cast::isActorActor() {
	return std::dynamic_pointer_cast<neb::core::actor::actor::base>(shared_from_this());
}
sp::shared_ptr<neb::core::actor::rigidactor::base>		neb::core::actor::util::Cast::isActorRigidActor() {
	return std::dynamic_pointer_cast<neb::core::actor::rigidactor::base>(shared_from_this());
}
sp::shared_ptr<neb::core::actor::rigidbody::base>		neb::core::actor::util::Cast::isActorRigidBody() {
	return std::dynamic_pointer_cast<neb::core::actor::rigidbody::base>(shared_from_this());
}
