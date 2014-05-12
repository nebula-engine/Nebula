#include <Nebula/Scene/Util/Cast.hh>

Neb::Scene::Base_s              Neb::Scene::Util::Cast::isSceneBase() {
        return std::dynamic_pointer_cast<Neb::Scene::Base>(shared_from_this());
}

