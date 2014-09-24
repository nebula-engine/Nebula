
#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/scene/util/cast.hpp>

shared_ptr<neb::core::core::scene::base>		neb::core::core::scene::util::cast::isSceneBase() {
	auto scene(dynamic_pointer_cast<neb::core::core::scene::base>(shared_from_this()));
	return scene;
}

