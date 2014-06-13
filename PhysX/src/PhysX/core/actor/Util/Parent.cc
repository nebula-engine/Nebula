#include <Nebula/debug.hh>

#include <Nebula/App/Base.hh>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Parent.hh>
#include <Nebula/Scene/Base.hh>

neb::Actor::Util::Parent::Parent() {
}
sp::shared_ptr<neb::Scene::Base>			neb::Actor::Util::Parent::getScene() {
	NEBULA_ACTOR_BASE_FUNC;

	auto scene = isSceneBase();

	if(scene) return scene;

	auto actor = isActorBase();

	if(!actor) throw 0;

	return actor->getScene();
}

