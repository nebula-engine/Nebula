#include <gal/log/log.hpp>

#include <neb/core/util/log.hpp>
#include <neb/core/util/config.hpp>
#include <neb/core/util/debug.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/actor/util/parent.hpp>
#include <neb/core/core/scene/base.hpp>

neb::core::core::actor::util::parent::parent() {
}
neb::core::core::actor::util::parent::~parent() {
}
<<<<<<< HEAD
void							neb::core::core::actor::util::parent::init() {

}
void							neb::core::core::actor::util::parent::release() {

}
std::shared_ptr<neb::core::core::scene::base>		neb::core::core::actor::util::parent::getScene() {
	LOG(lg, neb::core::core::actor::sl, debug) << __FUNCSIG__;

	auto scene = isSceneBase();

	if(scene) return scene;

	auto actor = isActorBase();
	
	if(!actor) abort();
	
	auto parent = actor->parent_.lock();
	assert(parent);
	
	return parent->getScene();
}
=======
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507

