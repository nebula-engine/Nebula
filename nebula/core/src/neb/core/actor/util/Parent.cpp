#include <gal/log/log.hpp>
#include <neb/debug.hh>

//#include <neb/app/Base.hh>

#include <neb/core/actor/base.hpp>
#include <neb/core/actor/util/Parent.hh>
#include <neb/core/scene/base.hpp>

neb::core::actor::util::parent::parent() {
}
neb::core::actor::util::parent::~parent() {
}
void							neb::core::actor::util::parent::init() {

}
void							neb::core::actor::util::parent::release() {

}
sp::shared_ptr<neb::core::scene::base>			neb::core::actor::util::parent::getScene() {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;

	auto scene(::std::dynamic_pointer_cast<neb::core::scene::base>(shared_from_this()));

	if(scene) return scene;

	auto actor(::std::dynamic_pointer_cast<neb::core::actor::base>(shared_from_this()));

	if(!actor) throw 0;

	return actor->getScene();
}

