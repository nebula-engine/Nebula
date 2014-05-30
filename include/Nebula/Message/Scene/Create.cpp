
#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Message/Scene/Create.hpp>

void Neb::Message::Scene::Create::load(Neb::Scene::Base_s scene) {
	i_ = scene->i_;
	scene_.ptr_ = scene;//.reset(Neb::App::Base::global()->factories_.scene_base_->alloc(scene->hash_code()));
}



