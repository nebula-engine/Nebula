#include <Nebula/Scene/Util/Cast.hh>
#include <Nebula/Scene/Base.hh>

sp::shared_ptr<neb::core::scene::base>              neb::core::scene::util::cast::isSceneBase() {
        return sp::dynamic_pointer_cast<neb::core::scene::base>(shared_from_this());
}

