#include <Nebula/Scene/Util/Cast.hh>
#include <Nebula/Scene/Base.hh>

sp::shared_ptr<neb::scene::base>              neb::scene::util::cast::isSceneBase() {
        return sp::dynamic_pointer_cast<neb::scene::base>(shared_from_this());
}

