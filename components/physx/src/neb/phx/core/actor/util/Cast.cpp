
#include <neb/phx/core/actor/rigiddynamic/base.hpp>
#include <neb/phx/core/actor/rigidstatic/base.hpp>
#include <neb/phx/core/actor/util/cast.hpp>

std::shared_ptr<neb::phx::core::actor::base>				neb::phx::core::actor::util::cast::isPxActorBase() {
	return std::dynamic_pointer_cast<neb::phx::core::actor::base>(shared_from_this());
}
std::shared_ptr<neb::phx::core::actor::actor::base>			neb::phx::core::actor::util::cast::isPxActorActorBase() {
	return std::dynamic_pointer_cast<neb::phx::core::actor::actor::base>(shared_from_this());
}
std::shared_ptr<neb::phx::core::actor::rigidactor::base>			neb::phx::core::actor::util::cast::isPxActorRigidActorBase() {
	return std::dynamic_pointer_cast<neb::phx::core::actor::rigidactor::base>(shared_from_this());
}
std::shared_ptr<neb::phx::core::actor::rigidbody::base>			neb::phx::core::actor::util::cast::isPxActorRigidBodyBase() {
	return std::dynamic_pointer_cast<neb::phx::core::actor::rigidbody::base>(shared_from_this());
}
std::shared_ptr<neb::phx::core::actor::rigiddynamic::base>		neb::phx::core::actor::util::cast::isPxActorRigidDynamicBase() {
	return std::dynamic_pointer_cast<neb::phx::core::actor::rigiddynamic::base>(shared_from_this());
}
std::shared_ptr<neb::phx::core::actor::rigidstatic::base>		neb::phx::core::actor::util::cast::isPxActorRigidStaticBase() {
	return std::dynamic_pointer_cast<neb::phx::core::actor::rigidstatic::base>(shared_from_this());
}


