
#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Message/Scene/Create.hpp>

Neb::Message::Scene::Create::Create() {
}
void Neb::Message::Scene::Create::load(Neb::Scene::Base_s scene) {
	scene_.ptr_ = scene;
}



