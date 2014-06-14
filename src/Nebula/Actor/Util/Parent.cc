#include <Nebula/debug.hh>

#include <Nebula/App/Base.hh>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Parent.hh>
#include <Nebula/Scene/Base.hh>

neb::core::actor::util::parent::parent() {
}
void					neb::core::actor::util::parent::init() {

}
sp::shared_ptr<neb::Scene::base>			neb::core::actor::util::parent::getScene() {
	NEBULA_ACTOR_BASE_FUNC;

	auto scene = isSceneBase();

	if(scene) return scene;

	auto actor = isActorBase();

	if(!actor) throw 0;

	return actor->getScene();
}

