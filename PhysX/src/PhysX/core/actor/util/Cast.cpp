
#include <PhysX/core/actor/rigiddynamic/base.hpp>
#include <PhysX/core/actor/rigidstatic/base.hpp>
#include <PhysX/core/actor/util/cast.hpp>

sp::shared_ptr<phx::core::actor::base>				phx::core::actor::util::cast::isPxActorBase() {
	return sp::dynamic_pointer_cast<phx::core::actor::base>(shared_from_this());
}
sp::shared_ptr<phx::core::actor::actor::base>			phx::core::actor::util::cast::isPxActorActorBase() {
	return sp::dynamic_pointer_cast<phx::core::actor::actor::base>(shared_from_this());
}
sp::shared_ptr<phx::core::actor::rigidactor::base>		phx::core::actor::util::cast::isPxActorRigidActorBase() {
	return sp::dynamic_pointer_cast<phx::core::actor::rigidactor::base>(shared_from_this());
}
sp::shared_ptr<phx::core::actor::rigidbody::base>		phx::core::actor::util::cast::isPxActorRigidBodyBase() {
	return sp::dynamic_pointer_cast<phx::core::actor::rigidbody::base>(shared_from_this());
}
sp::shared_ptr<phx::core::actor::rigiddynamic::base>		phx::core::actor::util::cast::isPxActorRigidDynamicBase() {
	return sp::dynamic_pointer_cast<phx::core::actor::rigiddynamic::base>(shared_from_this());
}
sp::shared_ptr<phx::core::actor::rigidstatic::base>		phx::core::actor::util::cast::isPxActorRigidStaticBase() {
	return sp::dynamic_pointer_cast<phx::core::actor::rigidstatic::base>(shared_from_this());
}

