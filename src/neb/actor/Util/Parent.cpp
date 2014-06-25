#include <gal/log/log.hpp>
#include <neb/debug.hh>

#include <neb/app/Base.hh>

#include <neb/core/actor/Base.hh>
#include <neb/core/actor/Util/Parent.hh>
#include <neb/core/scene/Base.hh>

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

	auto scene = isSceneBase();

	if(scene) return scene;

	auto actor = isActorBase();

	if(!actor) throw 0;

	return actor->getScene();
}

