#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/Util/Cast.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>


sp::shared_ptr<neb::core::actor::base>				neb::core::actor::util::cast::isActorBase() {
        return sp::dynamic_pointer_cast<neb::core::actor::base>(shared_from_this());
}
sp::shared_ptr<neb::core::actor::actor::base>			neb::core::actor::util::cast::isActorActor() {
	return sp::dynamic_pointer_cast<neb::core::actor::actor::base>(shared_from_this());
}
sp::shared_ptr<neb::core::actor::rigidactor::base>			neb::core::actor::util::cast::isActorRigidActor() {
	return sp::dynamic_pointer_cast<neb::core::actor::rigidactor::base>(shared_from_this());
}
sp::shared_ptr<neb::core::actor::rigidbody::base>			neb::core::actor::util::cast::isActorRigidBody() {
	return sp::dynamic_pointer_cast<neb::core::actor::rigidbody::base>(shared_from_this());
}
