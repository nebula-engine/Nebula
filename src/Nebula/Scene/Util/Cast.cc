#include <Nebula/Scene/Util/Cast.hh>
#include <Nebula/Scene/Base.hh>

sp::shared_ptr<neb::Scene::base>              neb::Scene::util::cast::isSceneBase() {
        return sp::dynamic_pointer_cast<neb::Scene::base>(shared_from_this());
}

