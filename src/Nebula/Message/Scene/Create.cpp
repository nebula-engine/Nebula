
#include <Nebula/app/Base.hh>
#include <Nebula/core/scene/Base.hh>
#include <Nebula/message/Scene/Create.hpp>

neb::message::scene::Create::Create() {
}
void neb::message::scene::Create::load(sp::shared_ptr<neb::core::scene::base> scene) {
	scene_.ptr_ = scene;
}



