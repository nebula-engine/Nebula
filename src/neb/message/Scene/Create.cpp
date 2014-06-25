
#include <neb/app/Base.hh>
#include <neb/core/scene/Base.hh>
#include <neb/message/Scene/Create.hpp>

neb::message::scene::Create::Create() {
}
void neb::message::scene::Create::load(sp::shared_ptr<neb::core::scene::base> scene) {
	scene_.ptr_ = scene;
}



