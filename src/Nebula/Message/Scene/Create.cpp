
#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Message/Scene/Create.hpp>

neb::message::scene::Create::Create() {
}
void neb::message::scene::Create::load(sp::shared_ptr<neb::scene::base> scene) {
	scene_.ptr_ = scene;
}



