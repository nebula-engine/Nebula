#include <Nebula/debug.hpp>
#include <Nebula/Actor/Base.hpp>
#include <Nebula/Actor/Util/Parent.hh>
#include <Nebula/Scene/scene.hpp>

Neb::Actor::Parent::Parent():
	actors_(Neb::App::global()->factories_.actor_base_)
{
}
void					Neb::Actor::Parent::releaseActor(Neb::Actor::Util::index_type i) {
	auto it = actors_.find(i);
	
	if(it == actors_.cend()) throw 0;
	
	// release the actor
	it->second.ptr_->release();
	
	actors_.erase(it);
}
Neb::Scene::Base_s			Neb::Actor::parent::getScene() {
	NEBULA_ACTOR_BASE_FUNC;

	auto scene = isSceneBase();
	
	if(scene) return scene;
	
	auto actor = isActorBase();
	
	if(!actor) throw 0;
	
	return actor->getScene();
}

