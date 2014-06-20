
#include <PhysX/core/scene/util/cast.hpp>
#include <PhysX/core/scene/base.hpp>
#include <PhysX/core/scene/local.hpp>
#include <PhysX/core/scene/remote.hpp>

sp::shared_ptr<phx::core::scene::base>		phx::core::scene::util::cast::isPxSceneBase() {
        return sp::dynamic_pointer_cast<phx::core::scene::base>(shared_from_this());
}
sp::shared_ptr<phx::core::scene::local>		phx::core::scene::util::cast::isPxSceneLocal() {
        return sp::dynamic_pointer_cast<phx::core::scene::local>(shared_from_this());
}
sp::shared_ptr<phx::core::scene::remote>	phx::core::scene::util::cast::isPxSceneRemote() {
        return sp::dynamic_pointer_cast<phx::core::scene::remote>(shared_from_this());
}

