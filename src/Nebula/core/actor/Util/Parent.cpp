#include <Nebula/debug.hh>

#include <Nebula/app/Base.hh>

#include <Nebula/core/actor/Base.hh>
#include <Nebula/core/actor/Util/Parent.hh>
#include <Nebula/core/scene/Base.hh>

neb::core::actor::util::parent::parent() {
}
neb::core::actor::util::parent::~parent() {
}
void							neb::core::actor::util::parent::init() {

}
void							neb::core::actor::util::parent::release() {

}
sp::shared_ptr<neb::core::scene::base>			neb::core::actor::util::parent::getScene() {
	NEBULA_ACTOR_BASE_FUNC;

	auto scene = isSceneBase();

	if(scene) return scene;

	auto actor = isActorBase();

	if(!actor) throw 0;

	return actor->getScene();
}

