
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/actor/util/cast.hpp>

shared_ptr<neb::core::core::actor::base>		neb::core::core::actor::util::cast::isActorBase() {
	auto actor(dynamic_pointer_cast<neb::core::core::actor::base>(shared_from_this()));
	return actor;
}

