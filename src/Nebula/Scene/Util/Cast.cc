#include <Nebula/Scene/Util/Cast.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Scene/Local.hh>
#include <Nebula/Scene/Remote.hh>

sp::shared_ptr<neb::core::scene::base>			neb::core::scene::util::cast::isSceneBase() {
        return sp::dynamic_pointer_cast<neb::core::scene::base>(shared_from_this());
}
sp::shared_ptr<neb::core::scene::local>			neb::core::scene::util::cast::isSceneLocal() {
        return sp::dynamic_pointer_cast<neb::core::scene::local>(shared_from_this());
}
sp::shared_ptr<neb::core::scene::remote>		neb::core::scene::util::cast::isSceneRemote() {
        return sp::dynamic_pointer_cast<neb::core::scene::remote>(shared_from_this());
}

