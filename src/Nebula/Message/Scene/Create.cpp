
#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Message/Scene/Create.hpp>

neb::message::Scene::Create::Create() {
}
void neb::message::Scene::Create::load(sp::shared_ptr<neb::Scene::Base> scene) {
	scene_.ptr_ = scene;
}



