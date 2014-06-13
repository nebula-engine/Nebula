#include <Nebula/Scene/Util/Cast.hh>
#include <Nebula/Scene/Base.hh>

sp::shared_ptr<neb::Scene::Base>              neb::Scene::Util::Cast::isSceneBase() {
        return std::dynamic_pointer_cast<neb::Scene::Base>(shared_from_this());
}

