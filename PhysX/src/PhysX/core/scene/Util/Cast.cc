
#include <PhysX/core/scene/util/cast.hpp>
#include <PhysX/core/scene/base.hpp>

sp::shared_ptr<phx::core::scene::base>		phx::core::scene::util::cast::isPxSceneBase() {
        return sp::dynamic_pointer_cast<phx::core::scene::base>(shared_from_this());
}

